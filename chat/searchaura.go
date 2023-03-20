package main

import (
	"io/ioutil"
	"strings"
)

type Aura struct {
	Index string
	Id string
	Name string
	TimeCreated string
	TimeModified string
}

type AuraWord struct {
	Index string
	Word string
	AuraId string
	AuraName string
	TimeAdded string
}

func (c *Client) searchaura(auraname string) {
	auranameQuoted := "\"" + auraname + "\""
	auraData, err := ioutil.ReadFile(rootdir + "/aura/aura.csv")
	if err != nil {
		panic(err)
	}
	/*
	Index,Aura Id,Aura Name,Time Created,Time Modified,
	1,"1","Your Right To Be Rich","Mon 20 Mar 2023 02:42:32 GMT","Mon 20 Mar 2023 02:42:32 GMT",
	*/
	// The first line is title list and should be omitted.
	auraLines := strings.Split(string(auraData), "\n")[1:]
	var IsAuraFound bool = false
	for _, line := range auraLines {
		attributes := strings.Split(line, ",")
		aura := Aura {
			strings.TrimSpace(attributes[0]), 
			strings.TrimSpace(attributes[1]),
			strings.TrimSpace(attributes[2]),
			strings.TrimSpace(attributes[3]),
			strings.TrimSpace(attributes[4]),
		}

		if strings.EqualFold(aura.Name, auranameQuoted) {
			// Aura found.
			IsAuraFound = true
			// Check words with aura.Id and aura.Name
			wordsData, err := ioutil.ReadFile(rootdir + "/aura/words.csv")
			if err != nil {
				panic(err)
			}
			/*
			Index,Word,Aura Id,Aura Name,Time Added,
			1,dynamo,"1","Your Right To Be Rich","Mon 20 Mar 2023 02:42:32 GMT",
			2,premise,"1","Your Right To Be Rich","Mon 20 Mar 2023 02:42:32 GMT",
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
				if word.AuraId == aura.Id {
					if strings.EqualFold(word.AuraName, aura.Name) {
						aurawords = append(aurawords, word)
					} else {
						word.AuraName = aura.Name
						// Update word aura name
						c.send <- []byte("searchaura: deprecated word.AuraName found: " + word.AuraName + ". Auto fixed.")
					}
				}
			}
			if len(aurawords) > 0 {
				wordsStr := func (aurawords []AuraWord) string {
					var str string = ""
					for index, word := range aurawords {
						// Aura Word was already quoted.
						str += word.Word
						if index + 1 < len(aurawords) {
							str += ","
						}
					}
					return "[" + str + "]"
				}(aurawords)
				c.send <- []byte("searchaura: aura[" + auranameQuoted + "].words = " + wordsStr)
			} else {
				c.send <- []byte("searchaura: aura[" + auranameQuoted + "].words = null")
			}
			break
		}
	}
	if IsAuraFound == false {
		c.send <- []byte("searchaura: aura " + auranameQuoted + " not found.")
	}
}