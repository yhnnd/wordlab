std::map<int, std::string> SortClassify(const char * defLine, const set<int> preferredSortSymbols) {

    std::map<int, std::string> resultsMap;

//    cout << "\nSortClassify: defLine = \"" << std::string(defLine) << "\"" << endl;

    for (const auto& sortSymbol: preferredSortSymbols) {
        const std::map<int, string>::const_iterator iter = mapSortSymbols.find(sortSymbol);
        if (iter == mapSortSymbols.end()) {
            continue;
        }
        const string sort = iter->second;
        if (std::string(defLine).find("/" + sort + "/") != std::string::npos) {
//            cout << "SortClassify: checking sortSymbol: " << sortSymbol << ", sort: \"" << sort << "\"" << endl;
//            cout << "Matched sort \"" << sort << "\"" << endl;
            resultsMap.insert(*iter);
        }
    }
//    cout << "resultsMap.size = " << resultsMap.size() << endl;
	return resultsMap;
}
