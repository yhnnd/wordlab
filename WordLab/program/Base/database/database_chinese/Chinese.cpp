std::string getDefinitionLine(const int lth, const int lineNumber) {
    int NOL = 0;
    string line = "", definitionLine = "";
    ifstream fin;
    Library(fin, lth, lang::CH);
    while (!fin.eof()) {
        if (std::getline(fin, line)) {
            NOL++;
            if (NOL == lineNumber) {
                definitionLine = line;
                break;
            }
        } else {
            break;
        }
    }
    fin.close();
    return definitionLine;
}

struct definitionType {
    std::string sort;
    std::string text;
};

std::vector<struct definitionType> getWordDefinitions(const int lth, const int lineNumber) {
    std::vector<struct definitionType> definitionsVector;
    const std::string definitionLine = getDefinitionLine(lth, lineNumber);
    if (definitionLine.empty() == false) {
        const std::string::size_type beginPos = definitionLine.find(" ");
        if (beginPos != std::string::npos) {
            const std::string definitionsLineWithoutKeyword = definitionLine.substr(beginPos + 1);
            const std::vector<std::string> definitions = split(definitionsLineWithoutKeyword, ",");
            for (const auto & item: definitions) {
                struct definitionType definitionItem;
                // iterate every definition item.
                const std::string::size_type sortBeginPos = item.find("/");
                if (sortBeginPos != std::string::npos) {
                    const std::string::size_type sortEndPos = item.find("/", sortBeginPos + 1);
                    if (sortEndPos != std::string::npos) {
                        definitionItem.sort = item.substr(sortBeginPos + 1, sortEndPos - sortBeginPos - 1);
                        // parse translation text.
                        const std::string::size_type definitionBeginPos = item.find("@", sortEndPos + 1);
                        if (definitionBeginPos != std::string::npos) {
                            const std::string::size_type definitionEndPos = item.find_first_of("@;", definitionBeginPos + 1);
                            if (definitionEndPos != std::string::npos) {
                                definitionItem.text = item.substr(definitionBeginPos + 1, definitionEndPos - definitionBeginPos - 1);
                            }
                        }
                    }
                }
                definitionsVector.push_back(definitionItem);
            }
        }
    }
	return definitionsVector;
}