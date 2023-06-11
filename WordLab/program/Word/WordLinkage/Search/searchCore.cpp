void WLSearchCore(int lth, int NOL, const std::string s, const int index, const std::string colorCommand = "<grn-blk>") {
    const std::string searchInfo = colorCommand + "("
                                   + toString(lth) + "/" + toString(NOL) + "/" + toString(index) + " "
                                   + s.substr(0, lth) + ")";
    bsvLine(searchInfo.c_str());

    const std::string searchResult = WLChinese(lth, index, definitionsColors[0]);

//    if (bsvLineGetPlainText(searchResult.c_str()).length() > prerequisites::ScreenX) {

        std::vector<std::string> definitionsVector;
        std::string tempLine = "";

        for (int i = 0; i < searchResult.length(); ++i) {
            tempLine.append(1, searchResult[i]);
            if ((
                    i > 0
                    && (
                            /* a redirect label and target should be considered as a definition item */
                            searchResult.substr(i).find(") <") == 0
                            /* space between redirect target and definitions after it */
                            ||
                            searchResult.substr(i).find("\"<") == 0
                            /* the end of a phrase definitions (redirected from a word definition) */
                            ||
                            searchResult.substr(i).find("\" \"") == 0
                            /* the end of a phrase definition item */
                            || (
                                    tempLine.find(">( REDIRECT ") != std::string::npos
                                    &&
                                    tempLine.find(")<") != std::string::npos
                                    && (
                                            searchResult.substr(i).find(")<") == 0
                                            /* end of a redirect indicator */
                                            ||
                                            searchResult.substr(i).find(") \"") == 0
                                            /* end of a redirect indicator */
                                    )
                            ) || (
                                    searchResult.substr(i, 2) == ")<"
                                    && (
                                            tempLine.find(colorCommand) != std::string::npos
                                            || tempLine.find("(v)<") != std::string::npos
                                    )
                            )
                    )
            ) || i == searchResult.length() - 1) {
                if (trim(tempLine).find("\"[") == 0 && tempLine.find("]\"") == tempLine.length() - 2) {
                    /* definition item is of type "phrase definition redirect target indicator" */
                    tempLine = trim(trim(tempLine, " "), "\"");
                    tempLine.erase(0, 1);
                    tempLine.pop_back();
                    tempLine = "<wte-blk>( )<#red-ylw>( " + tempLine + " )";
                }
//                tempLine = "[" + toString(definitionsVector.size()) + "]" + tempLine;
                definitionsVector.push_back(tempLine);
//                printf("%s\n", tempLine.c_str());
                tempLine = "";
            }
        }

        const int maxDefsPerLine = 8;
        std::vector<std::string> resultLines = {};
        std::vector<std::string> definitionsInOneLine = {};

        // put definitions into lines.
        if (definitionsVector.size()) {
            for (int i = 0; i < definitionsVector.size(); ++i) {
                const std::string definition = definitionsVector[i];
                if (
                        (
                                bsvLineGetPlainText((join(definitionsInOneLine, "") + definition).c_str()).length() + bsvLineGetPlainText(searchInfo.c_str()).length() > prerequisites::ScreenX
                                /* definitionsInOneLine length exceeds maximum length. */
                                && definition.find("(v)<") == std::string::npos
                                /* "verified mark" "(v)" must be at the end of a line and must not be in the beginning of a line */
                        ) || (
                                definitionsInOneLine.size() == maxDefsPerLine
                                &&
                                /* make sure the "verified mark" not being positioned at the beginning of the line */
                                definition.find("(v)<") == std::string::npos
                                /* current definition item is not a "verified mark" "(v)" */
                        ) || (
                                definitionsInOneLine.size()
                                &&
                                definitionsInOneLine.back().find("(v)<") != std::string::npos
                        ) || (
                                definitionsInOneLine.size() > 1
                                /* there are more than one items in stashed line */
                                &&
                                definitionsInOneLine[0].find(">( REDIRECT ") != std::string::npos
                                /* in which the first item is a redirect indicator */
                                &&
                                definition.find(">( REDIRECT ") != std::string::npos
                                /* current definition item is a redirect indicator */
                        )
                ) {
                    resultLines.push_back(join(definitionsInOneLine, ""));
                    definitionsInOneLine.clear();
                }
                definitionsInOneLine.push_back(definition);
            }

            if (definitionsInOneLine.size()) {
                resultLines.push_back(join(definitionsInOneLine, ""));
                definitionsInOneLine.clear();
            }
        }

        for (int i = 0; i < resultLines.size(); ++i) {
//            printf("\n%d \"%s\"", i, resultLines[i].c_str());
            if (i > 0) {
                printf("\n");
                std::cout << setfill(' ') << std::left << std::setw(bsvLineGetPlainText(searchInfo.c_str()).length()) << "";
            }
            bsvLine((" " + trim(resultLines[i], " ")).c_str());
        }
//    } else {
//        bsvLine((" " + trim(searchResult, " ")).c_str());
//    }

    WLHistory.RecordAnswer(s.substr(0, lth), 1);
}
