package main

import (
	"io/ioutil"
	"strconv"
	"strings"
	"fmt"
	"os"
)

func (c *Client) addword(message string) TypeResult {
	// Find the index of the equals sign in the message.
	equalsIndex := strings.Index(string(message), "=")
	// Extract the substring before the equals sign.
	word := message[0:equalsIndex]
	// Extract the substring after the equals sign.
	defs := string(message)[equalsIndex+1:]
	var result TypeResult
	result.Found = false
	if (len(word) <=0 || len(word) > 30) {
		c.send <- []byte("addword 21: word is not valid.")
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
		if word > temp {
		} else if word == temp {
			c.send <- []byte("addword 39: word exists.")
			return result
		} else {
			result.Index = index
			result.Found = true
		}
	}
	
	c.send <- []byte("addword 47: index = " + strconv.Itoa(result.Index))
	f, err := os.Create(tmpdb_en_dir)
	if err != nil {
		panic(err)
	}
	defer f.Close()
	result.Index = -1
	result.Found = false
	for index, elem := range words {
		temp := elem[0:len(word)]
		if word > temp {
		} else if word == temp {
			c.send <- []byte("addword 59: word exists.")
			return result
		} else if result.Found == false {
			_, err := f.WriteString(word + "\n")
			if err != nil {
				panic(err)
			}
			result.Index = index
			result.Found = true
		}
		_, err := f.WriteString(temp + "\n")
		if err != nil {
			panic(err)
		}
	}
	f.Sync()

	fmt.Printf("Addword: adding %q=%q to chinese database.\n", word, defs)
	// Open original database
	chineseData, err := ioutil.ReadFile(db_cn_dir)
	if err != nil {
		panic(err)
	}
	defLines := strings.Split(string(chineseData), "\n")
	// Creating temp database
	f, err = os.Create(tmpdb_cn_dir)
	if err != nil {
		panic(err)
	}
	defer f.Close()
	for index, defLine := range defLines {
		temp := defLine[0:len(word)]
		if word > temp {
		} else if word == temp {
			c.send <- []byte("addword 93: word definition exists.")
			return result
		} else if index == result.Index {
			_, err := f.WriteString(word + " " + defs + "\n")
			if err != nil {
				panic(err)
			}
		}
		_, err := f.WriteString(defLine + "\n")
		if err != nil {
			panic(err)
		}
	}
	f.Sync()
	os.Rename(db_en_dir, db_en_dir + ".prev")
	os.Rename(tmpdb_en_dir, db_en_dir)
	os.Rename(db_cn_dir, db_cn_dir + ".prev")
	os.Rename(tmpdb_cn_dir, db_cn_dir)
	c.send <- []byte("addword 111: word definition added.")
	return result
}