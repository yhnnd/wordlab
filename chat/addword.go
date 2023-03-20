package main

import (
	"io/ioutil"
	"strconv"
	"strings"
	"fmt"
	"os"
	"unicode"
)

type TypeAddWordResult struct {
	IsExisted bool		`json:"isexisted"`
	IsIndexed bool		`json:"isindexed"`
	Index int			`json:"index"`
	Total int			`json:"total"`
	DefsIndex int		`json:"defsindex"`
	DefsTotal int		`json:"defstotal"`
	TotalLeft int		`json:"totalleft"`
	TotalRight int		`json:"totalright"`
	IsWordAdded bool	`json:"iswordadded"`
	IsDefsAdded bool	`json:"isdefsadded"`
	Message string		`json:"message"`
}


















func (c *Client) addword(message string) TypeAddWordResult {
	// Find the index of the equals sign in the message.
	equalsIndex := strings.Index(string(message), "=")
	// Extract the substring before the equals sign.
	word := string(message)[0:equalsIndex]
	// Extract the substring after the equals sign.
	defs := string(message)[equalsIndex+1:]
	var result TypeAddWordResult
	result.IsExisted = false
	result.IsIndexed = false
	result.Total = 0
	result.TotalLeft = 0
	result.TotalRight = 0
	if (len(word) <=0 || len(word) > 30) {
		c.send <- []byte("addword 57: word is not valid.")
		return result
	}
	var db_en_dir = rootdir + "/en/english" + strconv.Itoa(len(word)) + ".csv"
	var tmpdb_en_dir = rootdir + "/en/english" + strconv.Itoa(len(word)) + ".csv.tmp"
	var db_cn_dir = rootdir + "/ch/chinese" + strconv.Itoa(len(word)) + ".csv"
	var tmpdb_cn_dir = rootdir + "/ch/chinese" + strconv.Itoa(len(word)) + ".csv.tmp"
	englishData, err := ioutil.ReadFile(db_en_dir)
	if err != nil {
		panic(err)
	}
	words := strings.Split(string(englishData), "\n")
	// Find a place where words before this place were smaller than this word 
	// and words after this place were greater than it.
	for index, elem := range words {
		temp := elem[0:len(word)]
		if strings.ToLower(temp) < strings.ToLower(word) {
			if result.IsIndexed == true {
				c.send <- []byte("addword 75: error: database damaged. words not correctly ordered.")
				return result
			}
			result.TotalLeft ++
			result.Total ++
		} else if strings.EqualFold(word, temp) {
			c.send <- []byte("addword 81: word exists. unable to add word. use update.")
			return result
		} else if strings.ToLower(temp) > strings.ToLower(word) {
			if result.IsIndexed == false {
				result.Index = index
				result.IsIndexed = true
			}
			result.TotalRight ++
			result.Total ++
		} else {
			result.Message = "addword 91: error: cannot compare temp " + temp + " with word " + word
			c.send <- []byte(result.Message)
			return result
		}
	}
	if (result.Total == len(words)) {
		if result.IsIndexed {
			c.send <- []byte("addword 98: total = " + strconv.Itoa(len(words)) + ", index = " + strconv.Itoa(result.Index))
		} else if result.TotalRight == 0 {
			result.Index = result.Total
			result.IsIndexed = true
			c.send <- []byte("addword 102: total = " + strconv.Itoa(len(words)) + ", index = " + strconv.Itoa(result.Index))
		} else {
			result.Message = "addword 104: error: cannot index word " + word
			c.send <- []byte(result.Message)
			return result
		}
	} else {
		result.Message = "addword 109: error: result.Total = " + strconv.Itoa(result.Total) + " should be " + strconv.Itoa(len(words))
		c.send <- []byte(result.Message)
		return result
	}
	// Creating temp words database
	f, err := os.Create(tmpdb_en_dir)
	if err != nil {
		panic(err)
	}
	defer f.Close()
	result.IsWordAdded = false
	result.Total = 0
	// Adding word to temp words database
	for index, elem := range words {
		temp := elem[0:len(word)]
		if strings.EqualFold(word, temp) {
			result.Message = "addword 124: word exists. word adding aborted."
			c.send <- []byte(result.Message)
			result.IsExisted = true
			return result
		} else if index == result.Index {
			_, err := f.WriteString(word)
			if err != nil {
				panic(err)
			}
			if index + 1 < len(words) {
				// The last element should not have newline symbol.
				_, err := f.WriteString("\n")
				if err != nil {
					panic(err)
				}
			}
			result.IsWordAdded = true
			result.Total ++
		}
		_, err := f.WriteString(temp)
		if err != nil {
			panic(err)
		}
		if index + 1 < len(words) {
			// The last element should not have newline symbol.
			_, err := f.WriteString("\n")
			if err != nil {
				panic(err)
			}
		}
		result.Total ++
		// If new word's Index is last index + 1, append new word to the end of file
		if index + 1 == len(words) && index + 1 == result.Index && result.IsWordAdded == false {
			// The last element should not have newline symbol.
			_, err := f.WriteString("\n" + word)
			if err != nil {
				panic(err)
			}
			result.IsWordAdded = true
			result.Total ++
		}
	}
	f.Sync()
	// Word adding validation
	if result.IsWordAdded {
		if result.Total < len(words) + 1 {
			result.IsWordAdded = false
			result.Message = "addword 171: error: data lost when adding word. aborted."
			c.send <- []byte(result.Message)
			return result
		} else if result.Total > len(words) + 1 {
			result.IsWordAdded = false
			result.Message = "addword 176: error: data duplicated when adding word. aborted."
			c.send <- []byte(result.Message)
			return result
		}
	} else {
		result.Message = "addword 181: error: failed to add word. aborted."
		c.send <- []byte(result.Message)
		return result
	}
	// Adding definition
	defLineToAdd := word + " " + defs
	fmt.Printf("Addword 187: adding %q to chinese database.\n", defLineToAdd)
	// Open original definition database
	chineseData, err := ioutil.ReadFile(db_cn_dir)
	if err != nil {
		panic(err)
	}
	defLines := strings.Split(string(chineseData), "\n")
	if (len(words) == len(defLines)) {
		result.IsDefsAdded = false
		result.DefsTotal = 0
		result.DefsIndex = 0
	} else {
		result.Message = "addword 199: error: definitions total " + strconv.Itoa(len(defLines)) + " does not match words total " + strconv.Itoa(len(words))
		c.send <- []byte(result.Message)
		return result
	}
	// Creating temp definition database
	f, err = os.Create(tmpdb_cn_dir)
	if err != nil {
		panic(err)
	}
	defer f.Close()
	for index, defLine := range defLines {
		if (len(defLine) <= len(word)) {
			result.Message = "addword 211: error: word definition database damaged."
			c.send <- []byte(result.Message)
			return result
		}
		var temp string = defLine[0:strings.Index(defLine, " ")]
		temp = strings.TrimSpace(temp)
		// Trim unexpected invisible characters in a utf8 encoded string.
		temp = strings.TrimFunc(temp, func(r rune) bool {
			return !unicode.IsGraphic(r)
		})
		if (len(temp) != len(word)) {
			result.Message = "addword 222: len(" + temp + ") = " + strconv.Itoa(len(temp)) + ", len(" + word + ") = " + strconv.Itoa(len(word)) + ", unable to compare temp " + temp + " with word " + word
			c.send <- []byte(result.Message)
			return result
		}
		// Compare temp with word. 
		// temp should be lesser than the word if its index is lesser than the word.
		// temp should be greater than the word if its index is greater than the word.
		if strings.ToLower(temp) < strings.ToLower(word) {
			if result.IsDefsAdded {
				result.Message = "addword 231: error: word definition database damaged."
				c.send <- []byte(result.Message)
				return result
			}
		} else if strings.EqualFold(word, temp) {
			result.Message = "addword 236: error: word definition exists."
			c.send <- []byte(result.Message)
			return result
		} else if strings.ToLower(temp) > strings.ToLower(word) {
			if index < result.Index {
				result.Message = "addword 241: error: word definition database damaged. temp " + temp + ".Index = " + strconv.Itoa(index) + ". It should be greater than result.Index = " + strconv.Itoa(result.Index)
				c.send <- []byte(result.Message)
				return result
			} else if index == result.Index {
				_, err := f.WriteString(defLineToAdd)
				if err != nil {
					panic(err)
				}
				if index + 1 < len(defLines) {
					// The last element should not have newline symbol.
					_, err := f.WriteString("\n")
					if err != nil {
						panic(err)
					}
				}
				result.IsDefsAdded = true
				result.DefsIndex = index
				result.DefsTotal ++
			}
		} else {
			result.Message = "addword 261: error: unable to compare temp " + temp + " with word " + word
			c.send <- []byte(result.Message)
			return result
		}
		_, err := f.WriteString(defLine)
		if err != nil {
			panic(err)
		}
		if index + 1 < len(defLines) {
			// The last element should not have newline symbol.
			_, err := f.WriteString("\n")
			if err != nil {
				panic(err)
			}
		}
		result.DefsTotal ++
		// If new definition's Index is last index + 1, append new definition to the end of file
		if index + 1 == len(defLines) && index + 1 == result.Index && result.IsDefsAdded == false {
			// The last element have no newline symbol.
			_, err := f.WriteString("\n" + defLineToAdd)
			if err != nil {
				panic(err)
			}
			result.IsDefsAdded = true
			result.DefsIndex = index + 1
			result.DefsTotal ++
		}
	}
	f.Sync()
	// Definition adding validation
	if result.IsDefsAdded == false {
		result.Message = "addword 292: error: definition adding failed."
		c.send <- []byte(result.Message)
		return result
	}
	if result.DefsTotal < len(defLines) + 1 {
		result.IsDefsAdded = false
		result.Message = "addword 298: error: data lost when adding definition. aborted."
		c.send <- []byte(result.Message)
		return result
	} else if result.DefsTotal > len(defLines) + 1 {
		result.IsDefsAdded = false
		result.Message = "addword 303: error: data duplicated when adding definition. aborted."
		c.send <- []byte(result.Message)
		return result
	}
	// backup original english database
	os.Rename(db_en_dir, db_en_dir + ".prev")
	// overwrite original english database
	os.Rename(tmpdb_en_dir, db_en_dir)
	// backup original definition database
	os.Rename(db_cn_dir, db_cn_dir + ".prev")
	// overwrite original definition database
	os.Rename(tmpdb_cn_dir, db_cn_dir)
	// word adding and definition adding done.
	result.Message = "addword 316: word definition added."
	c.send <- []byte(result.Message)
	return result
}