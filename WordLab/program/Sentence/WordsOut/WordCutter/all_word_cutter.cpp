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


bool sts::WordCutter(char *word) {
    int nAffix = 0, trimLth = 0, wordLth = strlen(word), max = filelines(AffixCutRoute,true);
    char AffixTexts[max][LINEMAX], AffixDefs[max][LINEMAX];
    fileIn(AffixTexts, AffixCutRoute);
    fileIn(AffixDefs, AffixAddRoute);

    wordcuttercheck(word, wordLth, &nAffix, &trimLth);

    if (nAffix == 0) {
        return false;
    }

    const char ch = AskChar("remove \"", AffixTexts[nAffix], "\"?");

    if (ch == 13 || ch == 10) {
        wordcutterremove(word, nAffix);
        strclr(word, wordLth - trimLth);
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
    int searchResultOfWordAfterTrimmed = getChineseOfWord(word, defsOfWordAfterTrimmed, sizeof(defsOfWordAfterTrimmed));


    if (affixPtr->isPrefix()) {
        // If Prefix Matched.
        const auto prefix_defs = AffixDefs[nAffix];
        // Print Prefix Definition
        this->pushWordAndDefs(affixPtr->getText(), prefix_defs, {"blk-", "-ylw"});
        if (searchResultOfWordAfterTrimmed > 0) {
            // Print Definition of Word After Trimmed.
            this->pushWordAndDefs(word, defsOfWordAfterTrimmed, {"pnk-", "-blk"});
            return true;
        } else {
            // recursive calling.
            return WordCutter(word);
        }
    } else if(affixPtr->isPostfix()) {
        // If Postfix Matched.
        if (searchResultOfWordAfterTrimmed > 0) {
            PUSH_WORD_AND_POSTFIX_DEFINITIONS:
            // Print Definition of Word After Trimmed.
            this->pushWordAndDefs(word, defsOfWordAfterTrimmed, {"pnk-", "-blk"});
            // Print Definition of Postfix.
            const auto postfix_defs = AffixDefs[nAffix];
            this->pushWordAndDefs(affixPtr->getText(), postfix_defs, {"blk-", "-ylw"});
            return true;
        } else {
            // If Postfixes that could trim "e", goto branch TRY_WORD_AFTER_TRIMMED_PLUS_E.
            const bool try_plus_e_first = (nAffix == sts::_affixSymbols::_postfix_ING || nAffix == sts::_affixSymbols::_postfix_ER || nAffix == sts::_affixSymbols::_postfix_OR);

            bool plus_e_is_tried = false;
            bool recursive_calling_is_tried = false;

            if (try_plus_e_first) {
                TRY_WORD_AFTER_TRIMMED_PLUS_E:
                // set plus_e_is_tried true for preventing endless recursive calling.
                if (plus_e_is_tried == true) {
                    return false;
                } else {
                    plus_e_is_tried = true;
                }
                // If word after trimmed is not valid, search word + 'e'
                const string wordPlusE = std::string(word) + "e";
                int searchResultOfWordAfterTrimmedPlusE = getChineseOfWord(
                        wordPlusE.c_str(), defsOfWordAfterTrimmed, sizeof(defsOfWordAfterTrimmed));
                if (searchResultOfWordAfterTrimmedPlusE) {
                    // Print definition of word after trimmed + "e"
                    this->pushWordAndDefs(wordPlusE, defsOfWordAfterTrimmed, {"blu-", "-blk"});
                    // Print Definition of Postfix.
                    const auto postfix_defs = AffixDefs[nAffix];
                    this->pushWordAndDefs(affixPtr->getText(), postfix_defs, {"blk-", "-ylw"});
                    return true;
                } else {
                    // word after trimmed is not valid. word after trimmed + 'e' is not valid either.
                    goto TRY_POSTFIX_RECURSIVE_CALLING;
                }
            } else {
                TRY_POSTFIX_RECURSIVE_CALLING:
                // set recursive_calling_is_tried true for preventing endless recursive calling.
                if (recursive_calling_is_tried == true) {
                    return false;
                } else {
                    recursive_calling_is_tried = true;
                }
                int resultValue = WordCutter(word);
                // Print Postfix Definition
                if (resultValue) {
                    PUSH_POSTFIX_DEFINITION:
                    const auto postfix_defs = AffixDefs[nAffix];
                    cout << "pushWordAndDefs affixPtr->getText() = " << affixPtr->getText() << ", postfix_defs = " << postfix_defs << endl;
                    this->pushWordAndDefs(affixPtr->getText(), postfix_defs, {"blk-", "-ylw"});
                    return true;
                } else {
                    goto TRY_WORD_AFTER_TRIMMED_PLUS_E;
                }
            }
        }
    } else if (nAffix > 0) {
        // If affix is neither prefix nor postfix (God knows what's kind of affix that is).
        if (searchResultOfWordAfterTrimmed > 0) {
            // Print Definition of Word After Trimmed.
            this->pushWordAndDefs(word, defsOfWordAfterTrimmed, {"pnk-", "-blk"});
            return true;
        }
    }
    return false;
}
