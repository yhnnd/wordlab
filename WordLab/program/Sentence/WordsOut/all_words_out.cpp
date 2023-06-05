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

    if (
            this->wordGroups.size() == 0 // Is First Word.
            ||
            (this->wordGroups.end() - 1)->defZh.size() == 0 // Previous Word has no Defs.
            || (
                    (this->wordGroups.end() - 1)->defZh.size()// Previous Word has Defs.
                    && (
                    // Previous Word's Defs ends with alpha.
                    isalpha( *( (this->wordGroups.end() - 1)->defZh.end() - 1) )
                    ||
                    // Previous Word's Defs is not valid.
                    (this->wordGroups.end() - 1)->defsColor.foregroundColor == "red-"
                    )
            )
    ) {
        this->pushWordAndDefs(s[rwout], string(s[rwout].txt) + " ", {"red-", "-blk"});
    } else {
        this->pushWordAndDefs(s[rwout], "_" + string(s[rwout].txt) + " ", {"red-", "-blk"});
    }

    return 0;
}



void sts::WordsOutCore() {
    if (this->wordIsPhrase[this->rwout] == true) {
        return;
    }

    int r;
    for (r = 0; r < this->prepositions.size(); r++) {
        if (this->rwout == this->prepositions[r].begin.pos) {
            this->pushWordAndDefs("", this->prepositions[r].begin.defs, {"cyn-", "-blk"});
            return;
        }
    }

    SmartTranslater();

    if (strlen(this->s[this->rwout].txt) == 0 && this->wordIsPhrase[this->rwout - 1] == true) {
        // Scenario: "pass" + "on" + "".
        return;
    }

    for (r = 0; r < this->prepositions.size(); r++) {
        if (this->rwout == this->prepositions[r].end.pos) {
            this->pushWordAndDefs("", this->prepositions[r].end.defs, {"cyn-", "-blk"});
        }
    }
}



//更新时间 2014/6/17
void sts::WordsOut() {

//    if (show_debug_message) {
//        printf("\nrwin = %d\n", rwin);
//    }

    const int numOfWords = this->rwin;

    memset(this->wordIsPhrase, 0, sizeof (this->wordIsPhrase));

    std::string improve = "";
    for (this->rwout = 0; this->rwout <= numOfWords;) {
//        if (this->configs.show_debug_message) {
//            printf("\nrwin = %d, rwout = %d, word = \"%s\"\n", this->rwin, this->rwout, this->s[this->rwout].txt);
//        }

        int phraseLth = PhrasesChecker(rwout);// pink
        if (phraseLth > 0) {
            for (int i = 0; i < phraseLth; ++i) {
                this->wordIsPhrase[this->rwout + i] = true;
            }
            this->rwout += phraseLth;
            continue;
        }

//        if (show_debug_message) {
//            printf("\nPhrases Check Done.\n");
//        }
        // yellow
        improve = "";
//#include "Framework/wlo-improvements/uppercase.cpp"
        //此插件修复STS Smart Translater无法翻译大写英语的问题


//#include "Framework/wlo-improvements/to.cpp"
        //解决 to 无法翻译成 "去" 的问题. n.(!v.) + to + v.
        if (
                rwout + 1 <= numOfWords
                &&
                strcmp(s[rwout].txt,"to") == 0
                &&
                wordSortIncludes(s[rwout+1].txt, {2, 5, 6})
        ) {
            improve = "去";
        }

//#include "Framework/wlo-improvements/so.cpp"
        //解决 so 无法翻译成 "如此" 的问题.
        if(
                rwout + 1 <= numOfWords
                &&
                strcmp(s[rwout].txt,"so") == 0
                &&
                wordSortIncludes(s[rwout+1].txt, {3, 4})
        ) {
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
        if (
                rwout + 1 <= numOfWords
                && (
                        strcmp(s[rwout].txt,"have") == 0
                        ||
                        strcmp(s[rwout].txt,"has") == 0
                        ||
                        strcmp(s[rwout].txt,"had") == 0
        )
           && wordSortIncludes(s[rwout+1].txt, {1, 3, 4, 7, 8, 10}) == 0
        ) {
            improve = "已经";
        }

//#include "Framework/wlo-improvements/more.cpp"
        //解决More无法在形容词及副词前翻译成 "更" 的问题.//adj./adv.
        if (
                rwout + 1 <= numOfWords
                &&
                strcmp(s[rwout].txt,"more") == 0
                &&
                wordSortIncludes(s[rwout+1].txt, {3, 4})
        ) {
            improve = "更";
        }

//#include "Framework/wlo-improvements/be+v.cpp"
        //解决 be 无法在动词过去式前翻译成 "被" 的问题.
        if (
                rwout + 1 <= numOfWords
                && (
                        strcmp(s[rwout].txt,"be") == 0
                        ||
                        strcmp(s[rwout].txt,"being") == 0
                        ||
                        strcmp(s[rwout].txt,"been") == 0
                ) && (
                        SortEX(s[rwout + 1].txt, "verb") == 0
                        ||
                        strindex(s[rwout + 1].txt, "ed") != -1
                )
        ) {
            improve = "被";
        }


        if (strcmp(s[rwout].txt,"miss") == 0) {
            const string tempdefs[2] = {"错过", "想念"};
            for (int i = 0; i < 2; ++ i) {
                const char key = AskChar("将",s[rwout].txt, "翻译为", tempdefs[i], "?");
                if (key == KEY_CARRIAGE_RETURN || key == KEY_NEW_LINE) {
                    improve = tempdefs[i];
                }
            }
        }


        if (improve != "") {
            this->pushWordAndDefs(s[rwout].txt, improve, {"ylw-", "-blk"});
            this->rwout++;
            continue;
        }


        WordsOutCore();

        this->rwout++;
    }

    // Copy Modified Sentence to sModified.
    this->copySentence(this->sModified, this->s, this->rwout);
    // Restore Sentence from sOriginal.
    this->copySentence(this->s, this->sOriginal, this->rwin);

    if(punct=='?') {
        this->inquiryEndFromPunct = getInquiryEndByPunct(this->punct);
        const string inquiryEndDefs = this->getInquiryEndDefs(this->inquiryEndFromPunct);
        this->pushDefs(inquiryEndDefs, {"ylw-", "-blk"});
        if (this->configs.show_debug_message) {
            printf("\npunct = %d '%c' inquiryEndFromPunct = %d\n", this->punct, this->punct, this->inquiryEndFromPunct);
        }
    }

    if(ispunct(punct)) {
        this->pushPunctAndDefs(punct, toString(punct), {"grn-", "-blk"});
    }
}




void sts::PrintWordTranslation(const wordGroup currentWordGroup) {
    recordColor(colorprev, "PrintWordTranslation");
    const string foregroundColor = currentWordGroup.defsColor.foregroundColor;
    const string backgroundColor = currentWordGroup.defsColor.backgroundColor;
    setForegroundColorAndBackgroundColor(foregroundColor, backgroundColor);
    printf("%s", currentWordGroup.defZh.c_str());
    resetColor(colorprev, "PrintWordTranslation");
    return;
}




// Wednesday May 03 Year 2023
void sts::PrintSentenceTranslation() {
    for (int i = 0; i  <  this->wordGroups.size(); ++i) {
        PrintWordTranslation(this->wordGroups[i]);
    }
}
