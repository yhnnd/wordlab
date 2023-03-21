package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
	"strconv"
	"strings"
)

func handleTranslate(w http.ResponseWriter, r *http.Request) {
	var result TypeResult
	result.Pathname = r.URL.Path
	r.ParseForm()
	if r.Form["callback"] != nil {
		if len(r.Form) > 0 {
			var word string
			for k, v := range r.Form {
				if k == "word" {
					fmt.Printf("handleTranslate (line 72): %s = %q\n", k, v[0])
					word = v[0]
				}
			}
			if word == "" {
				result.Message = "parameter word not given"
			} else {
				result.Word = word
				result.Lth = len(word)
				englishData, err := ioutil.ReadFile(rootdir + "/en/english" + strconv.Itoa(len(word)) + ".csv")
				if err != nil {
					panic(err)
				}
				words := strings.Split(string(englishData), "\n")
				result.Found = false
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
						tempDefs := strings.Split(defLine, ",")
						for defn, tempDef := range tempDefs {
							if defn == 0 {
								continue
							}
							text := tempDef
							sort := strings.Split(tempDef, "/")[1]
							chinese := tempDef[strings.Index(tempDef, "@"):strings.LastIndex(tempDef, ";")+1]
							result.Defs = append(result.Defs, TypeDef{Text: text, Sort: sort, Chinese: chinese})
							fmt.Printf("handleTranslate (line 107): sort = %q, chinese = %q\n", sort, chinese)
						}
						result.DefN = len(result.Defs)
						break
					}
				}
				if result.Found == false {
					result.Message = fmt.Sprintf("word %q not found", word)
				} else {
					result.Message = "word has been found"
				}
			}
		} else {
			result.Message = "no parameters"
		}
		JsonResult, err := json.MarshalIndent(result, "", "    ")
		if err != nil {
			panic(err)
		}
		fmt.Fprintf(w, "%s(%s)", r.Form["callback"][0], JsonResult)
	} else {
		result.Message = "callback not given"
		fmt.Fprintln(w, result.Message)
	}
}