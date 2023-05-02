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
    if (AskChar("Use Phrase (", tostring(phraseLth), ") \"", getPhraseLine(phraseLth, phrase), "\"?") == 13) {
        return true;
    }
    return false;
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
            colorrecord(prevColor);
            colorset(lightpurple);
            cout << phraseDef;
            colorreset(prevColor);
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
        phrasesRoute += tostring(currentPhraseLth);
        phrasesRoute += PhraseRouteB;
//        printf("PhrasesChecker: wordsNumLeft = %d, currentPhraseLth = %d, phrasesRoute = %s\n",
//               wordsNumLeft, currentPhraseLth, phrasesRoute.c_str());
        if (PhrasesCheckerCore(rwout, currentPhraseLth, phrasesRoute.c_str())) {
            return currentPhraseLth;
        }
    }
    return 0;
}
