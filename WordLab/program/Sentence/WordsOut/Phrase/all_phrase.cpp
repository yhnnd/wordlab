string sts::getPhraseLine(const unsigned int phraseLth, const vector<string> phrase) {
    if (phraseLth > phrase.size()) {
        return "#[Invalid Phrase]#";
    } else {
        std::string phraseLine = "";
        for (int i = 0; i < phraseLth; ++i) {
            if (i > 0) {
                phraseLine += " ";
            }
            phraseLine += phrase[i];
        }
        return phraseLine;
    }
}

bool sts::PhraseCheckerAsk(const unsigned int phraseLth, const vector<string> phrase) {
    if (this->configs.show_debug_message) {
        ::_Show = true;
        ::_AskOnce = true;
    }
    const int keyCode = AskChar("Use Phrase (", toString(phraseLth), ") \"", getPhraseLine(phraseLth, phrase), "\"?");
    if (this->configs.show_debug_message) {
        printf("\nPhraseCheckerAsk: keyCode = %d\n", keyCode);
    }
//    Carriage Return (Enter) = CR = 13 = '\r'
//    Line Feed (New Line) = LF = 10 = '\n'
    if (keyCode == 13 /* \r */|| keyCode == 10/* \n */) {
        return true;
    }
    return false;
}


void sts::PhraseCheckerUsePhrase(const unsigned int phraseLth, const vector<string> phrase, const vector<string> phraseDefs) {
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

    int choice = 0;
    if (phraseDefs.size() > 1) {
        if (this->configs.word_translation.manually_select_definition) {
            vector<string> menu;
            menu.push_back("choose one definition");
            for (vector<string>::const_iterator it = phraseDefs.begin(); it != phraseDefs.end(); ++it) {
                menu.push_back(*it);
            }
            choice = chooseFromMenu({6, 8}, 40, phraseDefs);
        }
    }
    tempWordGroup.defZh = phraseDefs[choice];
    // Push Current temporary wordGroup to wordGroups.
    this->wordGroups.push_back(tempWordGroup);
}


bool sts::PhraseCheckerCoreKernel(const int rwout, const unsigned int phraseLth, const vector<string> phrase, const vector<string> phraseDefs) {
    int i;
    for (i = 0; i < phraseLth; ++i) {
        if (phrase[i] != s[rwout + i].txt) {
            return false;
        }
    }
    if (i == phraseLth) {
        // Phrase Matched
        if (this->configs.show_debug_message) {
            printf("\nPhraseCheckerCoreKernel: Matched Phrase: \"%s\" phraseDef = \"%s\"\n",
                   sts::getPhraseLine(phraseLth, phrase).c_str(), join(phraseDefs, ",").c_str());
            printf("\ncurrentCursor: x = \"%d\", y = \"%d\"\n", getxy().X, getxy().Y);
        }
        const bool userReply = PhraseCheckerAsk(phraseLth, phrase);
        if (userReply == true) {
            // Use The Matched Phrase.
            this->PhraseCheckerUsePhrase(phraseLth, phrase, phraseDefs);
        } else {
            if (this->configs.show_debug_message) {
                printf("\nPhraseCheckerCoreKernel: You reject the matched phrase: \"%s\" phraseDef = \"%s\"\n",
                       sts::getPhraseLine(phraseLth, phrase).c_str(), join(phraseDefs, ",").c_str());
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
        if (phrase.size() < phraseLth + 1) {
            printf("\n%s: %s\n", "PhrasesCheckerCore: phrase line is in bad format", line.c_str());
            getch();
            return false;
        } else {
            // phrase.size() > phraseLth + 1 means that the phrase has more than one definition.
            vector<string> phraseDefs;
            for (int i = phraseLth; i < phrase.size(); ++i) {
                const string phraseDef = phrase[i];
                phraseDefs.push_back(phraseDef);
            }
            if (phraseDefs.empty()) {
                printf("\n%s: %s\n", "PhrasesCheckerCore: phrase defs loading failed", line.c_str());
                getch();
                return false;
            }
//            if (this->configs.show_debug_message) {
//                printf("PhrasesCheckerCore: phrase: \"%s\" phraseDef = \"%s\"\n",
//                       sts::getPhraseLine(phraseLth, phrase).c_str(), join(phraseDefs, ",").c_str());
//                getch();
//            }
            if (PhraseCheckerCoreKernel(rwout, phraseLth, phrase, phraseDefs)) {
                fin.close();
                return true;
            }
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
