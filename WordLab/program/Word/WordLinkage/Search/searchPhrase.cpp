struct phraseSearchResult getPhraseDefinitions(const int phraseLth, const std::vector<std::string> phrase, const bool ignoreCase) {

    const std::string route = PhraseRouteA + toString(phraseLth) + PhraseRouteB;
    ifstream fin(route);

    struct phraseSearchResult result;

    if (fin) {
        result.phraseLth = 0;
        result.phrase = {};
        result.lineNo = 0;

        const std::string searchKey = "," + join(phrase, ",") + ",";

//        printf ("phraseLth = %d, phrase = \"%s\"\n", phraseLth, searchKey.c_str());
//        getch();

        const auto isMatchedIgnoreCase = [] (const std::string line, const std::string searchKey) {
            const std::string src = line.substr(0, searchKey.length());
            if (strnicmp(src.c_str(), searchKey.c_str(), searchKey.length()) == 0) {
                const char key = popup("do you mean \"", trim(replace(src, ",", " ")), "\" ?", 3000);
                return key == KEY_NEW_LINE || key == KEY_CARRIAGE_RETURN;
            } else {
                return false;
            }
        };

        std::string line = "";

        while (std::getline(fin, line)) {
            ++ result.lineNo;
            if (line.find(searchKey) == 0 || isMatchedIgnoreCase(line, searchKey) == true) {
                fin.close();
                result.status = phraseSearchResultStatus::succeeded;
                result.phraseLth = phraseLth;
                result.phrase = split(line.substr(0, searchKey.length()), ",");
                result.phraseDefinitionsLineInDb = line;
                result.phraseDefinitionsLineWithoutKeyword = line.erase(line.find_last_not_of(";") + 1).substr(searchKey.length());
                result.defsVector = split(result.phraseDefinitionsLineWithoutKeyword, ",");

                if (result.defsVector.size()) {

                    std::vector<bool> definitionsIsRedirect;
                    struct phraseSearchResult resultOfTargetWord, resultOfTargetPhrase;

                    for (int i = 0; i < result.defsVector.size(); ++i) {
                        const std::string defItem = result.defsVector[i];
                        if (defItem.find("/redirected./") != std::string::npos) {
                            // definition item is redirect definition.
                            definitionsIsRedirect.push_back(true);

                            const std::string beginTerm = "@target=\"";
                            const std::string::size_type beginPos = defItem.find(beginTerm);
                            if (beginPos != std::string::npos) {
                                const std::string target = trim(defItem.substr(beginPos + beginTerm.length()), "\"");
//                                printf("target = \"%s\"\n", target.c_str());
//                                getch();
                                if (target.find(" ") == std::string::npos) {
                                    // target is of type word
                                    const int index = Search(target.c_str(), target.length(), false);
                                    if (index > 0) {
                                        // target word is valid
                                        const auto definitions = getWordDefinitions(target.length(), index);
                                        if (definitions.size()) {
                                            // stash redirect target word. Search "phrase definition redirect target indicator".
                                            resultOfTargetWord.defsVector.push_back("[" + target + "]");
                                            // stash target word definitions.
                                            for (const auto & item: definitions) {
                                                resultOfTargetWord.defsVector.push_back(item.text);
                                            }
                                        }
                                    }
                                } else {
                                    // target is of type phrase
                                    const struct phraseSearchResult tempResult = getPhraseDefinitions(target, false);
                                    if (tempResult.status == phraseSearchResultStatus::succeeded) {
                                        // target phrase is valid
                                        // stash redirect target phrase. Search "phrase definition redirect target indicator".
                                        resultOfTargetPhrase.defsVector.push_back("[" + target + "]");
                                        // stash target phrase definitions.
                                        for (const std::string & definitionItem: tempResult.defsVector) {
                                            resultOfTargetPhrase.defsVector.push_back(definitionItem);
                                        }
                                    }
                                }
                            } else {
                                result.status = phraseSearchResultStatus::failed;
                                result.message = "invalid definition \"" + defItem + "\"";
                            }
                        } else {
                            // definition item is not redirect definition.
                            definitionsIsRedirect.push_back(false);
                        }
                    }

//                    printf("definitionsIsRedirect.size() = %zu\n", definitionsIsRedirect.size());
//                    printf("resultOfTargetWord.defsVector.size() = %zu\n", resultOfTargetWord.defsVector.size());
//                    printf("resultOfTargetPhrase.defsVector.size() = %zu\n", resultOfTargetPhrase.defsVector.size());
//                    getch();

                    // remove all redirect definitions
                    for (int i = 0, numOfRemoved = 0; i < definitionsIsRedirect.size(); ++i) {
                        if (definitionsIsRedirect[i] == true) {
                            result.defsVector.erase(result.defsVector.begin() + i - numOfRemoved);
                            ++numOfRemoved;
                        }
                    }

                    // append target word definitions
                    if (resultOfTargetWord.defsVector.size()) {
                        for (const std::string item: resultOfTargetWord.defsVector) {
                            result.defsVector.push_back(item);
                        }
                    }

                    // append target phrase definitions
                    if (resultOfTargetPhrase.defsVector.size()) {
                        for (const std::string item: resultOfTargetPhrase.defsVector) {
                            result.defsVector.push_back(item);
                        }
                    }

                }
                return result;
            }
        }

        fin.close();
        result.status = phraseSearchResultStatus::failed;
        return result;
    } else {
        result.status = phraseSearchResultStatus::failed;
        result.message = "cannot open file \"" + route + "\"";
        return result;
    }
}


struct phraseSearchResult getPhraseDefinitions(const std::string msg, const bool ignoreCase) {
    if (msg.find(" ") != std::string::npos) {
        std::vector<std::string> phrase = split(msg, " ");
        return getPhraseDefinitions(phrase.size(), phrase, ignoreCase);
    } else if (msg.find(",") != std::string::npos) {
        std::vector<std::string> phrase = split(msg, ",");
        return getPhraseDefinitions(phrase.size(), phrase, ignoreCase);
    } else {
        struct phraseSearchResult result;
        result.status = phraseSearchResultStatus::failed;
        result.message = "search failed. invalid phrase";
        return result;
    }
}


int WLSearchPhrase(const std::string msg, const bool ignoreCase) {

    const struct phraseSearchResult result = getPhraseDefinitions(msg, ignoreCase);

    if (result.status == phraseSearchResultStatus::succeeded) {

        const int BeginY = 5;

        recordColor(colorPrev, "WLSearchPhrase");

        clearScreen(0, BeginY, ScreenX, ScreenY - 1 - BeginY);
        setForegroundColorAndBackgroundColor("wte-", "-#gry");
        clearScreen(0, 3, ScreenX - 1, 8);

        gotoxy(0, BeginY);
        setForegroundColorAndBackgroundColor("grn-", "-blk");
        printf(" %d / %d \"%s\"", result.phraseLth, result.lineNo, join(result.phrase, " ").c_str());

        if (result.message.empty() == false) {
            setForegroundColorAndBackgroundColor("#red-", "-ylw");
            printf(" %s ", result.message.c_str());
        }

        if (result.defsVector.size()) {


            for (std::string defItem: result.defsVector) {
                if (defItem.find("[") == 0 && defItem.find("]") == defItem.length() - 1) {
                    // indicator of redirect target.
                    defItem.erase(0, 1);// remove "["
                    defItem.pop_back();// remove "]"
                    bsvLine(("<wte-blk>( )<#red-ylw>( " + defItem + " )").c_str());
                } else {
                    setForegroundColorAndBackgroundColor("ylw-", "-blk");
                    printf(" \"%s\"", defItem.c_str());
                }
            }

            setForegroundColorAndBackgroundColor("blk-", "-grn");
            printf("v");
            setForegroundColorAndBackgroundColor("blk-", "-ylw");
            printf("%zu\n", result.defsVector.size());
        }

        resetColor(colorPrev, "WLSearchPhrase");

        return result.lineNo;
    } else if (result.message.empty() == true) {
        return 0;
    } else {
        popup(setModeYIsConstant);
        popup("#offsetY=0;");
        popup(result.message, 0);
        return -1;
    }
}
