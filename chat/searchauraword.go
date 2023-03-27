package main

import (
	"io/ioutil"
	"strings"
)

func (c *Client) searchauraword(auraword string) {
	aurawordQuoted := "\"" + auraword + "\""
	wordsData, err := ioutil.ReadFile(rootdir + "/aura/words.csv")
	if err != nil {
		panic(err)
	}
	// (new Date()).toUTCString().split(",").join("")
	/*
	Index,Word,Aura Id,Aura Name,Time Added,
	1,"dynamo","1","Your Right To Be Rich","Mon 20 Mar 2023 02:42:32 GMT",
	2,"premise","1","Your Right To Be Rich","Mon 20 Mar 2023 02:42:32 GMT",
	*/
	wordsLines := strings.Split(string(wordsData), "\n")[1:]
	var aurawords []AuraWord
	for _, line := range wordsLines {
		attributes := strings.Split(line, ",")
		word := AuraWord {
			strings.TrimSpace(attributes[0]),
			strings.TrimSpace(attributes[1]),
			strings.TrimSpace(attributes[2]),
			strings.TrimSpace(attributes[3]),
			strings.TrimSpace(attributes[4]),
		}
		if strings.EqualFold(word.Word, aurawordQuoted) {
			aurawords = append(aurawords, word)
		}
	}
	if len(aurawords) > 0 {
		aurasStr := func (aurawords []AuraWord) string {
			var str string = ""
			for index, word := range aurawords {
				// Aura Name was already quoted.
				str += word.AuraName
				if index + 1 < len(aurawords) {
					str += ","
				}
			}
			return "[" + str + "]"
		}(aurawords)
		c.send <- []byte("searchauraword: word[" + aurawordQuoted + "].auras = " + aurasStr)
	} else {
		c.send <- []byte("searchauraword: word " + aurawordQuoted + " not found.")
	}
}