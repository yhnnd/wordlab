//嚴格的查找模塊
void sts::seekverb(int r0,int *r1,int rwin) {
    for(*r1=r0; *r1<rwin; ++*r1) {
        if(SortEX(s[*r1].txt,"verb")==0 && SortEX(s[*r1+1].txt,"verb")!=0) {
            break;
        }
    }
}


void sts::findVerb(const int r0, int *r1, const int max) {
    int pos = r0;
    for(; pos < max; ++pos) {
        const char * word = s[pos].txt;
        const char * wordNext = s[pos + 1].txt;
        if (wordSortIsVerb(word) == true && wordSortIsVerb(wordNext) == false) {
            *r1 = pos;
            break;
        }
    }
}



void sts::findConj(const int r0, int * r1, const int max) {
    int pos = r0;
    for(; pos < max; ++pos) {
        const char * word = s[pos].txt;
        const char * wordNext = s[pos + 1].txt;
        if (wordSortIsConj(word) == true && wordSortIsConj(wordNext) == false) {
            *r1 = pos;
            break;
        }
    }
}




//不嚴格的查找模塊
void sts::seekverbEX(int r0,int *r1,int rwin) {
    for(*r1=r0; *r1<rwin; ++*r1) {
        if(SortEX(s[*r1].txt,"verb")==0||SortEX(s[*r1+1].txt,"verb")!=0) {
            break;
        }
    }
}


//如果此單詞不符合, 繼續依次查找
//如果此單詞符合, 下一個單詞也符合, 繼續依次查找
void sts::seeknoun(int r0,int *r1,int rwin) {
    for(*r1=r0; *r1<rwin; ++(*r1)) {
        if (
                (SortEX(s[*r1].txt,"noun") == 0 && SortEX(s[*r1+1].txt,"REALNOUN")!=0)
                ||
                SortEX(s[*r1+1].txt,"noun") !=0
        ) {
             break;
        }
    }
}

//如果此單詞不符合, 繼續依次查找
//如果此單詞符合, 下一個單詞也符合, 停止查找
// n. = 1, adj. = 3, pron. = 8
void sts::seeknounEX(int findFrom,int *stopAt,int rwin) {
    int pos = findFrom;
    for (; pos < rwin; ++pos) {
        if (SortEX(s[pos].txt,"NOUN") == 0 && SortEX(s[pos + 1].txt,"REALNOUN") != 0) {
            *stopAt = pos;
            break;
        }
        if (wordSortIncludes(s[pos].txt, {1, 8}) && wordSortIncludes(s[pos + 1].txt,{1, 8}) == 0) {
            *stopAt = pos;
            break;
        }
    }
}


// Pattern: (pron. + adj. + noun.)
// Scenario: your main job.
// n. = 1, adj. = 3, pron. = 8
void sts::findNoun(const int findFrom, int *stopAt, const int max) {
    int pos = findFrom;
    for (; pos < max; ++pos) {
        if (
                wordSortIncludes(s[pos].txt, {1, 3, 8}) > 0
                && (
                        pos + 1 == max
                        ||
                        wordSortIncludes(s[pos + 1].txt,{1, 3, 8}) == 0
                )
        ) {
            *stopAt = pos;
            break;
        }
    }
}


//如果此單詞不符, 停止查找
//如果此單詞符合, 下一個單詞也符合, 繼續依次查找
void sts::skipnoun(int r0,int *r1,int rwin) {
    for(*r1=r0; *r1<rwin; ++(*r1)) {
        if(SortEX(s[*r1].txt,"noun")!=0) {
            break;
        }
    }
}


//如果此單詞不符, 繼續依次查找
//如果此單詞符合, 下一個單詞也符合, 繼續依次查找
void sts::seekad(int r0,int *r1,int rwin){
    for(*r1=r0;*r1<rwin;++*r1) {
        if(SortEX(s[*r1+1].txt,"ad.")!=0) {
            break;
        }
    }
}

//如果此單詞不符, 繼續依次查找
//如果此單詞符合, 下一個單詞也符合, 停止查找
void sts::seekadEX(int r0,int *r1,int rwin) {
    for(*r1=r0;*r1<rwin;++*r1) {
        if(SortEX(s[*r1+1].txt,"ad.")!=0) {
            break;
        }
    }
}

//如果此單詞不符, 停止查找
//如果此單詞符合, 下一個單詞也符合, 繼續依次查找
void sts::skipad(int r0,int *r1,int rwin){
    for(*r1=r0;*r1<rwin;++*r1) {
        if(SortEX(s[*r1+1].txt,"ad.")!=0) {
            break;
        }
    }
}

//如果此單詞不符, 停止查找
//如果此單詞符合, 下一個單詞也符合, 停止查找
void sts::skipadEX(int r0,int *r1,int rwin){
    for(*r1=r0;*r1<rwin;++*r1) {
        if(SortEX(s[*r1+1].txt,"ad.")!=0) {
            break;
        }
    }
}

//
void sts::seekaux(int r0,int *r1,int rwin) {
    for(*r1=r0; *r1<rwin; ++*r1) {
        if(SortEX(s[*r1+1].txt,"aux.")!=0) {
            break;
        }
    }
}

void sts::findAux(const int r0, int * r1, int max) {
    int pos = r0;
    for (; pos < max; ++pos) {
        if (wordSortIsAuxil(s[pos].txt) == true && wordSortIsAuxil(s[pos + 1].txt) == false) {
            *r1 = pos;
            break;
        }
    }
}

//
void sts::skipaux(int r0,int *r1,int rwin) {
    for(*r1=r0; *r1<rwin; ++*r1) {
        if(SortEX(s[*r1].txt,"aux.")!=0) {
            break;
        }
    }
}



int sts::finderr(int r0, int *r1, const char * sort, const char * tool, const char * alias) {
	if (*r1 == r0) {
		status(tool, " finding ", alias, " failed!");
	} else if(SortEX(s[*r1].txt, sort)) {
		status(tool, " finding ", alias, " error!");
		*r1 = r0;
	} else {
		status(tool," has found ",alias,"(",toString(*r1),s[*r1].txt,")");
	}
    return 0;
}



int sts::findCheck(const int r0, int *r1, const vector<string> checkSorts, const char * tool, const char * alias) {
    if (*r1 == r0) {
        status(tool, " finding ", alias, " failed!");
        return 0;
    }
    const char * word = s[*r1].txt;
    const string wordSorts = sortOfWord(word);
    for (const string sort: checkSorts) {
        if (wordSorts.find(sort) != std::string::npos) {
            // Success.
            status(tool," has found ",alias,"(",toString(*r1),s[*r1].txt,")");
            return 0;
        }
    }
    // Error.
    status(tool, " finding ", alias, " error!");
    *r1 = r0;// reset
    return 0;
}