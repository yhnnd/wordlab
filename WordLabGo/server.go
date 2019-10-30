package main

import (
	"strings"
	"strconv"
	"io/ioutil"
	"log"
	"fmt"
	"net/http"
	"os"
	"encoding/json"
	// iconv "github.com/djimenez/iconv-go"
)

var rootdir string = "files/lang-utf8"

func main() {
	// name1,err:=iconv.ConvertString(name,"GB2312","utf-8")
	var cmd string
	fmt.Printf("root dir = %q\n[S]tart server\n[C]onfig root dir\n[Q]uit server\n", rootdir)
	fmt.Scanf("%s", &cmd)
	if strings.EqualFold(cmd, "Q") || strings.EqualFold(cmd, "Quit") {
		fmt.Println("quit")
		os.Exit(0)
	} else if strings.EqualFold(cmd, "S") || strings.EqualFold(cmd, "Start") {
	} else if strings.EqualFold(cmd, "C") || strings.EqualFold(cmd, "Config") {
		fmt.Printf("input root dir:\n")
		fmt.Scanf("%s", &rootdir)
	} else {
		fmt.Println("unknown command!")
		os.Exit(0)
	}
	fmt.Printf("root dir is %q\n", rootdir)
	if _, err := ioutil.ReadFile(rootdir + "/en/english0.csv"); err != nil {
		fmt.Printf("root dir %q is not available!\n", rootdir)
		os.Exit(1)
	}
	http.HandleFunc("/translate", handler)
	http.HandleFunc("/search", handleSuggests)
	http.HandleFunc("/suggestions", handleSuggests)
	fmt.Println("server is running")
	log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

type TypeDef struct {
	Text string 	`json:"text"`
	Sort string 	`json:"sort"`
	Chinese string 	`json:"chinese"`
}

type TypeResult struct {
	Pathname string `json:"pathname"`
	Word string 	`json:"word"`
	Lth int 		`json:"lth"`
	Index int 		`json:"num"`
	Defs [] TypeDef `json:"defs"`
	DefN int 		`json:"defn"`
	Found bool		`json:"found"`
	Message string	`json:"message"`
}

func handler(w http.ResponseWriter, r *http.Request) {
	var result TypeResult
	result.Pathname = r.URL.Path
	r.ParseForm()
	if r.Form["callback"] != nil {
		if len(r.Form) > 0 {
			var word string
			for k, v := range r.Form {
				// fmt.Fprintf(w, "%s = %q\n", k, v[0])
				if k == "word" {
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


func strHasSubseq(line string, pattern string) bool {
	itr_line := 0
	len_line := len(line)
	itr_pattern := 0
	len_pattern := len(pattern)
	for itr_line != len_line && itr_pattern != len_pattern {
		if line[itr_line] == pattern[itr_pattern] {
			itr_pattern++
		}
		itr_line++
	}
	return itr_pattern == len_pattern
}

const (
	substrRatio = 0.5
	subseqRatio = 0.66
)

type TypeWordSuggestions struct {
	PrefixSuggestions [] string `json:"prefix-suggestions"`
	SubseqSuggestions [] string `json:"subseq-suggestions"`
}

func handleSuggests(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	if r.Form["callback"] != nil && r.Form["word"] != nil {
		var suggestions TypeWordSuggestions
		var keyword string = r.Form["word"][0]
		var lth float64 = float64(len(keyword))
		set := make(map[string]bool)
		allWords, err := ioutil.ReadFile(rootdir + "/words.txt")
		if err != nil {
			panic(err)
		}
		words := strings.Split(string(allWords), " ")
		for _, word := range words {
			if strings.Index(word,keyword) == 0 && lth/float64(len(word)) >= substrRatio {
				suggestions.PrefixSuggestions = append(suggestions.PrefixSuggestions, word)
				set[word] = true
			}
		}
		for _, word := range words {
			if(strHasSubseq(word,keyword) && lth/float64(len(word)) >= subseqRatio) {
				if _, ok := set[word]; ok {
					continue
				}
				suggestions.SubseqSuggestions = append(suggestions.SubseqSuggestions, word)
				set[word] = true
			}
		}
		JsonResult, err := json.MarshalIndent(suggestions, "", "    ")
		if err != nil {
			panic(err)
		}
		fmt.Fprintf(w, "%s(%s)", r.Form["callback"][0], JsonResult)
	} else {
		fmt.Fprintln(w, "callback or word not given")
	}
}