package main

import (
	"io/ioutil"
	"strconv"
	"strings"
	"fmt"
	"os"
	"unicode"
)








func (c *Client) updateword(message string) TypeResult {
	// Find the index of the equals sign in the message.
	equalsIndex := strings.Index(string(message), "=")
	// Extract the substring before the equals sign.
	word := string(message)[0:equalsIndex]
	// Extract the substring after the equals sign.
	defs := string(message)[equalsIndex+1:]
	var result TypeResult
	result.Found = false
	if (len(word) <=0 || len(word) > 30) {
		c.send <- []byte("updateword 29: word is not valid.")
		return result
	}
	var db_en_dir = rootdir + "/en/english" + strconv.Itoa(len(word)) + ".csv"
	// Only definition database needs to be updated.
	var db_cn_dir = rootdir + "/ch/chinese" + strconv.Itoa(len(word)) + ".csv"
	var tmpdb_cn_dir = rootdir + "/ch/chinese" + strconv.Itoa(len(word)) + ".csv.tmp"
	englishData, err := ioutil.ReadFile(db_en_dir)
	if err != nil {
		panic(err)
	}
	words := strings.Split(string(englishData), "\n")
	// Find the place of the word
	for index, elem := range words {
		temp := elem[0:len(word)]
		if strings.EqualFold(word, temp) {
			result.Index = index
			result.Found = true
			break
		}
	}
	if result.Found == false {
		c.send <- []byte("updateword 51: word not found")
		return result
	}
	c.send <- []byte("updateword 54: index = " + strconv.Itoa(result.Index))
	fmt.Printf("updateword 55: stashing %q=%q to temp definition database.\n", word, defs)
	// Open original definition database
	definitionData, err := ioutil.ReadFile(db_cn_dir)
	if err != nil {
		panic(err)
	}
	defLines := strings.Split(string(definitionData), "\n")
	// Creating temp definition database
	f, err := os.Create(tmpdb_cn_dir)
	if err != nil {
		panic(err)
	}
	defer f.Close()
	// Filter definition lines.
	filteredDefLines := []string{}
    for _, defLine := range defLines {
        if len(strings.TrimFunc(defLine, func(r rune) bool {
			return unicode.IsGraphic(r) == false || unicode.IsSpace(r) == true
		})) > 0 {
			defLine = strings.TrimSpace(defLine)
			filteredDefLines = append(filteredDefLines, defLine)
		}
    }
	if len(filteredDefLines) < len(defLines) {
		c.send <- []byte("updateword 79: word definition database damaged. auto fixed.")
		defLines = filteredDefLines
	}
	for index, defLine := range defLines {
		if (len(defLine) <= len(word)) {
			// If definitions line has been damaged. Auto fix it.
			c.send <- []byte("updateword 84: word definition database damaged at index = " + strconv.Itoa(index))
			if len(defLines) == len(words) && ((index > 0 && strings.HasPrefix(defLines[index-1], words[index-1])) || (index + 1 < len(defLines) && strings.HasPrefix(defLines[index+1], words[index+1]))) {
				// If auto fix is available
				_, err := f.WriteString(words[index] + " ,[autofix];")
				if err != nil {
					panic(err)
				}
				if index + 1 < len(defLines) {
					_, err := f.WriteString("\n")
					if err != nil {
						panic(err)
					}
				}
				c.send <- []byte("updateword 98: auto fixed.")
				continue
			} else {
				c.send <- []byte("updateword 101: definitions database damaged. auto fix failed.")
				return result
			}
		}
		// Extract word from defintion line.
		var IndexOfSpaceMark int = strings.Index(defLine, " ")
		if IndexOfSpaceMark < 0 {
			c.send <- []byte("updateword 108: definitions database damaged. auto fix failed.")
			return result
		}
		var temp string = defLine[0:IndexOfSpaceMark]
		// Trim unexpected invisible characters in a utf8 encoded string.
		temp = strings.TrimFunc(temp, func(r rune) bool {
			return !unicode.IsGraphic(r)
		})
		// Safety Check.
		if (len(temp) != len(word)) {
			c.send <- []byte("updateword 95: len(" + temp + ") = " + strconv.Itoa(len(temp)) + ", len(" + word + ") = " + strconv.Itoa(len(word)) + ", unable to compare temp " + temp + " with word " + word)
			return result
		}
		// Iterate to the place where word should be updated.
		if index == result.Index {
			if strings.EqualFold(word, temp) {
				_, err := f.WriteString(word + " " + defs)
				if err != nil {
					panic(err)
				}
				if index + 1 < len(defLines) {
					_, err := f.WriteString("\n")
					if err != nil {
						panic(err)
					}
				}
				c.send <- []byte("updateword 111: stashing word definition.")
			} else {
				c.send <- []byte("updateword 113: error: word definition database damaged.")
				return result
			}
		} else {
			_, err := f.WriteString(defLine)
			if err != nil {
				panic(err)
			}
			if index + 1 < len(defLines) {
				_, err := f.WriteString("\n")
				if err != nil {
					panic(err)
				}
			}
		}
	}
	f.Sync()
	c.send <- []byte("updateword 130: word definition stashed. now you can confirm to update it.")
	return result
}