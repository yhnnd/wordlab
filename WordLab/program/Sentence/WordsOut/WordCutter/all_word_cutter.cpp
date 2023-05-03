void sts::wordcuttercheck(char *currentWord, const int wordLth, int *resultAffixSymbol, int *trimLth) {
    int nAffix = 0, deLth = 0;

    for (auto it = this->mapAffixSymbolsToAffix.begin(); it != this->mapAffixSymbolsToAffix.end(); ++it) {
        // get current affix's symbol.
        const enum _affixSymbols currentAffixSymbol = it->first;
        // get current affix
        affix currentAffix = it->second;
        // get current affix's text
        const string affixText = currentAffix.getText();
        // get current affix's text length
        const unsigned short affixLth = affixText.length();
        // check affix type
        if (wordLth - affixLth > 0) {
            if (currentAffix.isPrefix()) {
                // if affix is prefix
                if (strindex(currentWord, affixText.c_str()) == 0) {
                    break;
                }
            } else if (currentAffix.isPostfix()) {
                // if affix is postfix
                if (strindex(currentWord, affixText.c_str()) == wordLth - affixLth) {
                    nAffix = currentAffixSymbol;
                    deLth = affixLth;
                    break;
                }
            }
        }
    }
    if (nAffix > 0) {
        *resultAffixSymbol = nAffix;
        *trimLth = deLth;
    }
    return;
}


void sts::wordcutterremove(char *word, const int nAffix) {
    if (nAffix <= 0) {
        return;
    }
    const std::map<sts::_affixSymbols, sts::affix> & theMap = this->mapAffixSymbolsToAffix;
    const std::map<sts::_affixSymbols, sts::affix>::const_iterator iter = theMap.find((enum _affixSymbols) nAffix);
    if (iter != theMap.end()) {
        sts::affix affix = iter->second;
        if (affix.isPrefix()) {
            const unsigned short affixLth = affix.length();
            if (affixLth > 0) {
                // Remove the prefix of the word.
                int i = 0;
                for (i = 0; word[i + affixLth] != 0; i++) {
                    word[i] = word[i + affixLth];
                }
                strclr(word, i);
            }
        }
    }
}


void sts::fileIn(char msg[][LINEMAX],const char *route) {
    int r = 0, r1 = 0;
    char c = 0;
    FILE * fp = fopen(route, "r");
    rewind(fp);
    while (true) {
        c = fgetc(fp);
        if (c == ';') {
            // Omit chars after ';'
            while (true) {
                c = fgetc(fp);
                if (c == '\n' || c == EOF) {
                    break;
                }
            }
        }
        if (c == EOF) {
            strclr(msg[r], r1);
            break;
        } else if (c == '\n') {
            strclr(msg[r], r1);
            r++;
            r1 = 0;
        } else {
            msg[r][r1++] = c;
        }
    }
    fclose(fp);
}


bool sts::WordCutter(char *s) {
    int nAffix = 0, trimLth = 0, wordLth = strlen(s), max = filelines(AffixCutRoute,true);
    char AffixTexts[max][LINEMAX], AffixDefs[max][LINEMAX];
    fileIn(AffixTexts, AffixCutRoute);
    fileIn(AffixDefs, AffixAddRoute);
    wordcuttercheck(s, wordLth, &nAffix, &trimLth);
    if (nAffix == 0) {
        return false;
    }

    const char ch = AskChar("remove \"", AffixTexts[nAffix], "\"?");
    if (ch == 13 || ch == 10) {
        wordcutterremove(s, nAffix);
        strclr(s, wordLth - trimLth);
    } else {
        return false;
    }

    const std::map<sts::_affixSymbols, sts::affix> & theMap = this->mapAffixSymbolsToAffix;
    const std::map<sts::_affixSymbols, sts::affix>::const_iterator iter = theMap.find((enum _affixSymbols) nAffix);
    sts::affix * affixPtr = nullptr;
    if (iter != theMap.end()) {
        affixPtr = (sts::affix *) & (iter->second);
    } else {
        return false;
    }

    char defsOfWordAfterTrimmed [32];
    int searchResultOfWordAfterTrimmed = getChineseOfWord(s, defsOfWordAfterTrimmed, sizeof(defsOfWordAfterTrimmed));

    if (nAffix == sts::_affixSymbols::_postfix_ING) {
        // Specified for postfix "-ing"
        if (searchResultOfWordAfterTrimmed > 0) {
            // Print Definition of Word After Trimmed.
            this->pushWordAndDefs(s, defsOfWordAfterTrimmed, {"pnk-", "-blk"});
            return true;
        } else {
            // If word after trimmed is not valid, search word + 'e'
            string temp = toString(s) + "e";
            if (getChineseOfWord(temp.c_str(), defsOfWordAfterTrimmed, sizeof(defsOfWordAfterTrimmed))) {
                // Print definition of word after trimmed + "e"
                this->pushWordAndDefs(s, defsOfWordAfterTrimmed, {"blu-", "-blk"});
                return true;
            } else {
                // word after trimmed is not valid. word after trimmed + 'e' is not valid either.
                return false;
            }
        }
    } else if (affixPtr->isPrefix()) {
        // If Prefix Matched.
        const auto prefix_defs = AffixDefs[nAffix];
        // Print Prefix Definition
        this->pushWordAndDefs(affixPtr->getText(), prefix_defs, {"blk-", "-ylw"});
        if (searchResultOfWordAfterTrimmed > 0) {
            // Print Definition of Word After Trimmed.
            this->pushWordAndDefs(s, defsOfWordAfterTrimmed, {"pnk-", "-blk"});
            return true;
        } else {
            // recursive calling.
            return WordCutter(s);
        }
    } else if(affixPtr->isPostfix()) {
        // If Postfix Matched.
        if (searchResultOfWordAfterTrimmed > 0) {
            // Print Definition of Word After Trimmed.
            this->pushWordAndDefs(s, defsOfWordAfterTrimmed, {"pnk-", "-blk"});
            return true;
        } else {
            // recursive calling.
            int resultValue = WordCutter(s);
            // Print Postfix Definition
            const auto postfix_defs = AffixDefs[nAffix];
            this->pushWordAndDefs(affixPtr->getText(), postfix_defs, {"blk-", "-ylw"});
            return resultValue;
        }
    } else if (nAffix > 0) {
        // If affix is neither prefix nor postfix (God knows what's kind of affix that is).
        if (searchResultOfWordAfterTrimmed > 0) {
            // Print Definition of Word After Trimmed.
            this->pushWordAndDefs(s, defsOfWordAfterTrimmed, {"pnk-", "-blk"});
            return true;
        }
    }
    return false;
}
