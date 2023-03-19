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
	if (len(word) <=0 || len(word) > 30) {
		c.send <- []byte("addword 36: word is not valid.")
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
				c.send <- []byte("addword 54: error: database damaged. words not correctly ordered.")
				return result
			}
			result.Total ++
		} else if strings.EqualFold(word, temp) {
			c.send <- []byte("addword 59: word exists. unable to add word. use update.")
			return result
		} else if strings.ToLower(temp) > strings.ToLower(word) {
			if result.IsIndexed == false {
				result.Index = index
				result.IsIndexed = true
			}
			result.Total ++
		} else {
			result.Message = "addword 68: error: cannot compare temp " + temp + " with word " + word
			c.send <- []byte(result.Message)
			return result
		}
	}
	if (result.Total == len(words)) {
		if result.IsIndexed {
			c.send <- []byte("addword 75: total = " + strconv.Itoa(len(words)) + ", index = " + strconv.Itoa(result.Index))
		} else {
			result.Message = "addword 77: error: cannot index word " + word
			c.send <- []byte(result.Message)
			return result
		}
	} else {
		result.Message = "addword 82: error: result.Total = " + strconv.Itoa(result.Total) + " should be " + strconv.Itoa(len(words))
		c.send <- []byte(result.Message)
		return result
	}
	// Adding word to temp english database
	f, err := os.Create(tmpdb_en_dir)
	if err != nil {
		panic(err)
	}
	defer f.Close()
	result.IsWordAdded = false
	result.Total = 0
	for index, elem := range words {
		temp := elem[0:len(word)]
		if strings.EqualFold(word, temp) {
			result.Message = "addword 97: word exists. word adding aborted."
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
	}
	f.Sync()
	// Word adding validation
	if (result.Total < len(words) + 1) {
		result.IsWordAdded = false
		result.Message = "addword 133: error: data lost when adding word. aborted."
		c.send <- []byte(result.Message)
		return result
	} else if (result.Total > len(words) + 1) {
		result.IsWordAdded = false
		result.Message = "addword 138: error: data duplicated when adding word. aborted."
		c.send <- []byte(result.Message)
		return result
	}
	// Adding definition
	defLineToAdd := word + " " + defs
	fmt.Printf("Addword 144: adding %q to chinese database.\n", defLineToAdd)
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
		result.Message = "addword 156: error: definitions total " + strconv.Itoa(len(defLines)) + " does not match words total " + strconv.Itoa(len(words))
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
			result.Message = "addword 168: error: word definition database damaged."
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
			result.Message = "addword 179: len(" + temp + ") = " + strconv.Itoa(len(temp)) + ", len(" + word + ") = " + strconv.Itoa(len(word)) + ", unable to compare temp " + temp + " with word " + word
			c.send <- []byte(result.Message)
			return result
		}
		// Compare temp with word. 
		// temp should be lesser than the word if its index is lesser than the word.
		// temp should be greater than the word if its index is greater than the word.
		if strings.ToLower(temp) < strings.ToLower(word) {
			if result.IsDefsAdded {
				result.Message = "addword 188: error: word definition database damaged."
				c.send <- []byte(result.Message)
				return result
			}
		} else if strings.EqualFold(word, temp) {
			result.Message = "addword 193: error: word definition exists."
			c.send <- []byte(result.Message)
			return result
		} else if strings.ToLower(temp) > strings.ToLower(word) {
			if index < result.Index {
				result.Message = "addword 198: error: word definition database damaged. temp " + temp + ".Index = " + strconv.Itoa(index) + ". It should be greater than result.Index = " + strconv.Itoa(result.Index)
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
				result.DefsTotal ++
			}
		} else {
			result.Message = "addword 217: error: unable to compare temp " + temp + " with word " + word
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
	}
	f.Sync()
	// Definition adding validation
	if result.IsDefsAdded == false {
		result.Message = "addword 237: error: definition adding failed."
		c.send <- []byte(result.Message)
		return result
	}
	if result.DefsTotal < len(defLines) + 1 {
		result.IsDefsAdded = false
		result.Message = "addword 243: error: data lost when adding definition. aborted."
		c.send <- []byte(result.Message)
		return result
	} else if result.DefsTotal > len(defLines) + 1 {
		result.IsDefsAdded = false
		result.Message = "addword 248: error: data duplicated when adding definition. aborted."
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
	result.Message = "addword 261: word definition added."
	c.send <- []byte(result.Message)
	return result
}