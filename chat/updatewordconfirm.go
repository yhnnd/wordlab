package main

import (
	"io/ioutil"
	"strconv"
	"strings"
	"fmt"
	"os"
)

/* 161 Preserved Space for adding codes in the future.
/* 162 To keep log code unaffected when adding extra codes,
/* 163 This space was allocated beforehand.
/* 
/* 
/* 
/* 167 */
func (c *Client) updatewordconfirm(message string) TypeResult {
	// Find the index of the equals sign in the message.
	equalsIndex := strings.Index(string(message), "=")
	// Extract the substring before the equals sign.
	word := message[0:equalsIndex]
	// Extract the substring after the equals sign.
	defs := string(message)[equalsIndex+1:]
	// Compose the definition line to update.
	stashedDefLine := word + " " + defs
	var result TypeResult
	result.Found = false
	if (len(word) <=0 || len(word) > 30) {
		c.send <- []byte("updatewordconfirm 180: word is not valid.")
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
		c.send <- []byte("updatewordconfirm 202: word not found")
		return result
	}
	c.send <- []byte("updatewordconfirm 205: index = " + strconv.Itoa(result.Index))
	fmt.Printf("updatewordconfirm 175: validating definition %q.\n", stashedDefLine)
	// Open temp definition database
	definitionData, err := ioutil.ReadFile(tmpdb_cn_dir)
	if err != nil {
		c.send <- []byte("updatewordconfirm 210: no stashed word definition found. nothing to update.")
		return result
	}
	defLines := strings.Split(string(definitionData), "\n")
	for index, defLine := range defLines {
		if index == result.Index {
			if defLine == stashedDefLine {
				c.send <- []byte("updatewordconfirm 217: word definition validation done.")
				break
			} else {
				c.send <- []byte("updatewordconfirm 220: error: word definition validation failed.")
				return result
			}
		}
	}
	// backup original words database
	// os.Rename(db_en_dir, db_en_dir + ".prev")
	// overwrite original words database
	// os.Rename(tmpdb_en_dir, db_en_dir)
	// backup original definitions database
	os.Rename(db_cn_dir, db_cn_dir + ".prev")
	// overwrite original definitions database
	os.Rename(tmpdb_cn_dir, db_cn_dir)
	c.send <- []byte("updatewordconfirm 227: word definition updated.")
	return result
}