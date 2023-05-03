int sts::SmartTranslater() {

//    printf("\ndef = \"");
//    printChineseOfWord(s[rwout].txt, 0);
//    printf("\"\n");

    if (isalpha(s[rwout].txt[0]) == false) {
        // Cannot translate non-word.
        this->pushWordAndDefs(s[rwout], s[rwout].txt, {"wte-", "-blk"});
        return 0;
    }

    char def[64];
    int result = getChineseOfWord(s[rwout].txt, def, sizeof(def));
    if (result > 0) {
        this->pushWordAndDefs(s[rwout], def, {"grn-", "-blk"});
        return 0;
    }

    if (WordCutter(s[rwout].txt) == 1) {
        return 0;
    }

    result = getChineseOfWord_S(s[rwout].txt, def, sizeof(def), 1);
    if ( result > 0 ) {
        this->pushWordAndDefs(s[rwout], def, {"ylw-", "-blk"});
        return 0;
    }

    this->pushWordAndDefs(s[rwout], s[rwout].txt, {"red-", "-blk"});
    return 0;
}



void sts::WordsOutCore() {
    int r;
    for (r=0; r < maxprep; r++) {
        if(rwout == preppos0[r]) {
            cout << preptrans0[r];
            return;
        }
    }

    SmartTranslater();

    for (r=0; r<maxprep; r++) {
        if (rwout==preppos1[r]) {
            cout<<preptrans1[r];
        }
    }
}



//更新时间 2014/6/17
void sts::WordsOut() {

//    if (show_debug_message) {
//        printf("\nrwin = %d\n", rwin);
//    }

    std::string improve = "";
    for(rwout = 0; rwout <= rwin; rwout++) {
//        if (show_debug_message) {
//            printf("\nrwin = %d, rwout = %d\n", this->rwin, rwout);
//        }

        rwout += PhrasesChecker(rwout);// pink

//        if (show_debug_message) {
//            printf("\nPhrases Check Done.\n");
//        }
        // yellow
        improve = "";
//#include "Framework/wlo-improvements/uppercase.cpp"
        //此插件修复STS Smart Translater无法翻译大写英语的问题


//#include "Framework/wlo-improvements/to.cpp"
        //解决 to 无法翻译成 "去" 的问题. n.(!v.) + to + v.
        if(strcmp(s[rwout].txt,"to")==0
        &&(WordSort(s[rwout+1].txt)==2
        ||WordSort(s[rwout+1].txt)==5
        ||WordSort(s[rwout+1].txt)==6)) {
            improve = "去";
        }

//#include "Framework/wlo-improvements/so.cpp"
        //解决 so 无法翻译成 "如此" 的问题.
        if(strcmp(s[rwout].txt,"so")==0
        &&(WordSort(s[rwout+1].txt)==3
        ||WordSort(s[rwout+1].txt)==4)) {
            improve = "如此";
        }

//#include "Framework/wlo-improvements/don't.cpp"
        //解决 don't 无法翻译成 "不" 的问题.
        if (strcmp(s[rwout].txt, "don't") == 0) {
            improve = "不";
        }

//#include "Framework/wlo-improvements/have.cpp"
        //解决 have 无法翻译成 "已经" 的问题.
//one of 2(v.) 5(vi.) 6(vt.) 9(auxil.)
        if((strcmp(s[rwout].txt,"have")==0
            ||strcmp(s[rwout].txt,"has")==0
            ||strcmp(s[rwout].txt,"had")==0)
           &&WordSort(s[rwout+1].txt)!=1
           &&WordSort(s[rwout+1].txt)!=3
           &&WordSort(s[rwout+1].txt)!=4
           &&WordSort(s[rwout+1].txt)!=7
           &&WordSort(s[rwout+1].txt)!=8
           &&WordSort(s[rwout+1].txt)!=10) {
            improve = "已经";
        }

//#include "Framework/wlo-improvements/more.cpp"
        //解决More无法在形容词及副词前翻译成 "更" 的问题.//adj./adv.
        if(strcmp(s[rwout].txt,"more")==0
        &&(WordSort(s[rwout+1].txt)==3
        ||WordSort(s[rwout+1].txt)==4)) {
            improve = "更";
        }

//#include "Framework/wlo-improvements/be+v.cpp"
        //解决 be 无法在动词过去式前翻译成 "被" 的问题.
        if(strcmp(s[rwout].txt,"be")==0
        ||strcmp(s[rwout].txt,"being")==0
        ||strcmp(s[rwout].txt,"been")==0) {
            if (SortEX(s[rwout + 1].txt, "verb") == 0
            || strindex(s[rwout + 1].txt, "ed") != -1) {
                improve = "被";
            }
        }

        if (strcmp(s[rwout].txt,"miss") == 0) {
            improve = "错过";
            if (AskChar("将",s[rwout].txt, "翻译为", improve, "?") == 13) {
            } else {
                improve = "想念";
            }
        }


        if (improve != "") {
            this->pushWordAndDefs(s[rwout].txt, improve, {"ylw-", "-blk"});
            continue;
        }


        WordsOutCore();
    }

    // Copy Modified Sentence to sModified.
    this->copySentence(this->sModified, this->s, this->rwout);
    // Restore Sentence from sOriginal.
    this->copySentence(this->s, this->sOriginal, this->rwin);

    if(punct=='?') {
        this->inquiryEndFromPunct = getInquiryEndByPunct(this->punct);
        const string inquiryEndDefs = this->getInquiryEndDefs(this->inquiryEndFromPunct);
        this->pushDefs(inquiryEndDefs, {"ylw-", "-blk"});
        if (show_debug_message) {
            cout << endl << "punct = \'" << punct << "\' inquiryEndFromPunct = " << this->inquiryEndFromPunct << endl;
        }
    }

    if(ispunct(punct)) {
        this->pushPunctAndDefs(punct, toString(punct), {"grn-", "-blk"});
    }
}




void sts::PrintWordTranslation(const wordGroup currentWordGroup) {
    const string foregroundColor = currentWordGroup.defsColor.foregroundColor;
    const string backgroundColor = currentWordGroup.defsColor.backgroundColor;
    setForegroundColorAndBackgroundColor(foregroundColor, backgroundColor);
    printf("%s", currentWordGroup.defZh.c_str());
    return;
}




// Wednesday May 03 Year 2023
void sts::PrintSentenceTranslation() {
    for (int i = 0; i  <  this->wordGroups.size(); ++i) {
        PrintWordTranslation(this->wordGroups[i]);
    }
}
