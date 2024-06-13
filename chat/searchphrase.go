package main

import (
	"io/ioutil"
	"strconv"
	"strings"
)

func (c *Client) wlsearchphrase(phraseStr string) TypeResult {
	var result TypeResult
	result.Found = false
	phraseLength := len(strings.Split(phraseStr, " "))
	phraseData, err := ioutil.ReadFile(rootdir + "/phrases/" + strconv.Itoa(phraseLength) + " word phrase.csv")
	if err != nil {
		panic(err)
	}
	phraseKey := "," + strings.ReplaceAll(phraseStr, " ", ",")
	phrases := strings.Split(string(phraseData), "\n")
	for index, elem := range phrases {
		if len(elem) < len(phraseKey) { // to prevent slice bounds out of range
			continue
		}
		temp := elem[0:len(phraseKey)]
		if strings.EqualFold(temp, phraseKey) {
			result.Index = index
			result.Found = true
			result.Message = elem
			break
		}
	}
	return result
}