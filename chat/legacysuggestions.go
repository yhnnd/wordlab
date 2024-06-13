package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
	"strings"
)

type TypeWordSuggestions struct {
	PrefixSuggestions [] string `json:"prefix-suggestions"`
	SubseqSuggestions [] string `json:"subseq-suggestions"`
}

type LegacySuggestions struct {
	TypeWordSuggestions
	substrRatio float64 //= 0.5
	subseqRatio float64 //= 0.66
}

func (s *LegacySuggestions) strHasSubseq(line string, pattern string) bool {
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


func (this *LegacySuggestions) handleSuggests(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	if r.Form["callback"] != nil && r.Form["word"] != nil {
		var keyword string = r.Form["word"][0]
		var lth float64 = float64(len(keyword))
		set := make(map[string]bool)
		allWords, err := ioutil.ReadFile(rootdir + "/EnglishVocabulary.txt")
		if err != nil {
			panic(err)
		}
		words := strings.Split(string(allWords), " ")
		this.PrefixSuggestions = this.PrefixSuggestions[:0]
		for _, word := range words {
			if strings.Index(word,keyword) == 0 && lth/float64(len(word)) >= this.substrRatio {
				this.PrefixSuggestions = append(this.PrefixSuggestions, word)
				set[word] = true
			}
		}
		this.SubseqSuggestions = this.SubseqSuggestions[:0]
		for _, word := range words {
			if this.strHasSubseq(word,keyword) && lth/float64(len(word)) >= this.subseqRatio {
				if _, ok := set[word]; ok {
					continue
				}
				this.SubseqSuggestions = append(this.SubseqSuggestions, word)
				set[word] = true
			}
		}
		JsonResult, err := json.MarshalIndent(this, "", "    ")
		if err != nil {
			panic(err)
		}
		fmt.Fprintf(w, "%s(%s)", r.Form["callback"][0], JsonResult)
	} else {
		fmt.Fprintln(w, "callback or word not given")
	}
}