std::string getRedirectDefinition(const std::string redirectFromKeyword, const std::string line, const int fontColor) {
    int lth = 0, number = 0;
    const std::string redirect_result_msg = ChineseRedirect(redirectFromKeyword, line, lth, number);
    const std::string indicatorTargetIsWord = "WORD ";
    const std::string indicatorTargetIsPhrase = "PHRASE ";
    if (lth > 0 && number > 0 && redirect_result_msg.find(indicatorTargetIsWord) == 0) {
        // target is of type word.
        const std::string targetWord = redirect_result_msg.substr(indicatorTargetIsWord.length());
        return "<ylw-#red>( REDIRECT )<#red-ylw>( " + targetWord + " )" + WLChinese(lth, number, fontColor);
    } else if (redirect_result_msg.find(indicatorTargetIsPhrase) == 0) {
        // target is of type phrase.
        const std::string targetPhrase = redirect_result_msg.substr(indicatorTargetIsPhrase.length());
        const struct phraseSearchResult phResult = getPhraseDefinitions(targetPhrase, false);
        if (phResult.status == phraseSearchResultStatus::succeeded) {
            const std::string phraseDefinition = phResult.defsVector[0];
            return "<ylw-#red>( REDIRECT Ph )<#red-ylw>( " + targetPhrase + " ) " + phraseDefinition;
        } else {
            return "<#red-ylw>( REDIRECT Ph )<ylw-#red>( " + targetPhrase + " ) " + phResult.message;
        }
    } else {
        return "<#red-ylw>( REDIRECT )<ylw-#red>( " + redirect_result_msg + " )";
    }
}


std::string WLChinese(int lth, int number, const int fontColor) {
	ifstream fin;
	Library(fin, lth, CH);

    int NOL = 0;
    std::string line = "";

	while (!fin.eof()) {
		if (std::getline(fin, line)) {
            ++NOL;
        }
		if (NOL == number) {

			fin.close();

			if (fontColor == 2) {// Interface for scan(A) engine
                return line.substr(0, lth);
            } else {
                if (line.find("/redirected./") != string::npos) {
                    // Addon that support redirect definition
                    const std::string redirectFromKeyword = line.substr(0, lth);

                    const std::vector<std::string> definitionsVector = split(trim(line.substr(lth), " "), ",");

                    std::string returnLine = "";
                    std::vector<std::string> stashedNonRedirectDefinitions = {};
                    std::vector<std::string> stashedRedirectDefinitions = {};

                    // Separate redirect and non-redirect definitions.
                    for (const std::string definitionItem: definitionsVector) {
                        if (definitionItem.find("/redirected./") != string::npos) {
                            stashedRedirectDefinitions.push_back(definitionItem);
                        } else {
                            stashedNonRedirectDefinitions.push_back("," + definitionItem);
                        }
                    }

                    // render non-redirect definitions first.
                    if (stashedNonRedirectDefinitions.size()) {
                        returnLine += WLChineseCore(join(stashedNonRedirectDefinitions, ""), fontColor);
                    }
                    // render redirect definitions.
                    for (const std::string redirectingDefinitionItem: stashedRedirectDefinitions) {
                        returnLine += getRedirectDefinition(redirectFromKeyword, redirectingDefinitionItem, fontColor);
                    }
                    return returnLine;
                } else {// PLAIN DEFINITION
                    return WLChineseCore(line.substr(lth), fontColor);
                }
            }
			break;
		}
	}
	fin.close();
	return "";
}
