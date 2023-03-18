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

func wlsearch(word string) TypeResult {
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
		temp := elem[0:len(word)]
		if word == temp {
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