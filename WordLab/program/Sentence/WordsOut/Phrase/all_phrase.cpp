string sts::getPhraseLine(const unsigned int phraseLth, const vector<string> phrase) {
    if (phraseLth > phrase.size()) {
        return "#[Invalid Phrase]#";
    } else {
        std::string phraseLine = "";
        for(auto iter = phrase.begin(); iter != phrase.end(); ++iter) {
            if (iter != phrase.begin()) {
                phraseLine += " ";
            }
            phraseLine += *iter;
        }
        return phraseLine;
    }
}

bool sts::PhraseCheckerAsk(const unsigned int phraseLth, const vector<string> phrase) {
    ::_AskOnce = true;
    const int keyCode = AskChar("Use Phrase (", toString(phraseLth), ") \"", getPhraseLine(phraseLth, phrase), "\"?");
    if (show_debug_message) {
        printf("\nPhraseCheckerAsk: keyChar = '%c' keyCode = %d\n", keyCode, keyCode);
    }
//    Carriage Return (Enter) = CR = 13 = '\r'
//    Line Feed (New Line) = LF = 10 = '\n'
    if (keyCode == 13 /* \r */|| keyCode == 10/* \n */) {
        return true;
    }
    return false;
}


void sts::PhraseCheckerUsePhrase(const unsigned int phraseLth, const vector<string> phrase, const string phraseDef) {
    // Push All words in phrase to phraseWords
    vector<word> phraseWords;
    for(int ph = 0; ph < phraseLth; ++ph) {
        word phraseWord;
        strcpy(phraseWord.txt, phrase[ph].c_str());
        phraseWords.push_back(phraseWord);
    }
    // Generate a temporary wordGroup
    wordGroup tempWordGroup;
    tempWordGroup.words = phraseWords;
    tempWordGroup.defsColor.foregroundColor = "pnk-";
    tempWordGroup.defsColor.backgroundColor = "-blk";
    tempWordGroup.defZh = phraseDef;
    // Push Current temporary wordGroup to wordGroups.
    this->wordGroups.push_back(tempWordGroup);
}


bool sts::PhraseCheckerCoreKernel(const int rwout, const unsigned int phraseLth, const vector<string> phrase, const string phraseDef) {
    int i;
    for (i = 0; i < phraseLth; ++i) {
        if (phrase[i] != s[rwout + i].txt) {
            return false;
        }
    }
    if (i == phraseLth) {
        // Phrase Matched
        if (show_debug_message) {
            printf("\nPhraseCheckerCoreKernel: Matched Phrase: \"%s\" phraseDef = \"%s\"\n",
                   sts::getPhraseLine(phraseLth, phrase).c_str(), phraseDef.c_str());
            printf("\ncurrentCursor: x = \"%d\", y = \"%d\"\n", getxy().X, getxy().Y);
        }
        const bool userReply = PhraseCheckerAsk(phraseLth, phrase);
        if (userReply == true) {
            // Use The Matched Phrase.
            this->PhraseCheckerUsePhrase(phraseLth, phrase, phraseDef);
        } else {
            if (show_debug_message) {
                printf("\nPhraseCheckerCoreKernel: You reject the matched phrase: \"%s\" phraseDef = \"%s\"\n",
                       sts::getPhraseLine(phraseLth, phrase).c_str(), phraseDef.c_str());
            }
        }
        return true;
    }
    return false;
}

bool sts::PhrasesCheckerCore(const int rwout, unsigned int phraseLth, const char * phraseRoute) {
    char ch;
    string line = "";
    ifstream fin(phraseRoute);
    if (!fin) {
        return false;
    }
    while (std::getline(fin, line)) {
        vector<string> phrase = split(line, ",;");
        if (phrase.size() == phraseLth + 1) {
            const string phraseDef = phrase[phraseLth];
//            if (show_debug_message) {
//                printf("PhrasesCheckerCore: phrase: \"%s\" phraseDef = \"%s\"\n",
//                       sts::getPhraseLine(phraseLth, phrase).c_str(), phraseDef.c_str());
//            }
            if (PhraseCheckerCoreKernel(rwout, phraseLth, phrase, phraseDef)) {
                fin.close();
                return true;
            }
        } else {
            cout << "PhrasesCheckerCore: phrase line is in bad format: " << line << endl;
            getch();
            break;
        }
    }
    fin.close();
    return false;
}

int sts::PhrasesChecker(const int rwout) {
    const int wordsNumLeft = this->rwin - rwout + 1;
    if (wordsNumLeft <= 0) {
        return 0;
    }
    int currentPhraseLth = phraseMaxWords;
    if (currentPhraseLth > wordsNumLeft) {
        currentPhraseLth = wordsNumLeft;
    }
    for (; currentPhraseLth > 0; --currentPhraseLth) {
        std::string phrasesRoute;
        phrasesRoute = PhraseRouteA;
        phrasesRoute += toString(currentPhraseLth);
        phrasesRoute += PhraseRouteB;
//        printf("PhrasesChecker: wordsNumLeft = %d, currentPhraseLth = %d, phrasesRoute = %s\n",
//               wordsNumLeft, currentPhraseLth, phrasesRoute.c_str());
        if (PhrasesCheckerCore(rwout, currentPhraseLth, phrasesRoute.c_str())) {
            return currentPhraseLth;
        }
    }
    return 0;
}
