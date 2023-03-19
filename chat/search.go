package main

import (
	"io/ioutil"
	"strconv"
	"strings"
)

const (
	rootdir = "../WordLabGo/files/lang-utf8"
)

type TypeResult struct {
	Index int 		`json:"num"`
	Found bool		`json:"found"`
	Message string	`json:"message"`
}

func (c *Client) wlsearch(word string) TypeResult {
	var result TypeResult
	result.Found = false
	if (len(word) > 30) {
		return result
	}
	englishData, err := ioutil.ReadFile(rootdir + "/en/english" + strconv.Itoa(len(word)) + ".csv")
	if err != nil {
		panic(err)
	}
	words := strings.Split(string(englishData), "\n")
	for index, elem := range words {
		if len(elem) < len(word) {
			result.Message = "wlsearch 32: error: database damaged. temp = " + elem + ", word = " + word
			c.send <- []byte(result.Message)
			return result
		}
		temp := elem[0:len(word)]
		if strings.EqualFold(word, temp) {
			result.Index = index
			result.Found = true
			chineseData, err := ioutil.ReadFile(rootdir + "/ch/chinese" + strconv.Itoa(len(word)) + ".csv")
			if err != nil {
				panic(err)
			}
			defLines := strings.Split(string(chineseData), "\n")
			defLine := strings.TrimSpace(defLines[index])
			result.Message = defLine
			break
		}
	}
	return result
}