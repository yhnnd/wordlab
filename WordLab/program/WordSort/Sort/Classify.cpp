std::map<int, std::string> SortClassify(const char * defLine, const set<int> preferredSortSymbols) {

    static std::map<int, std::string> mapSortSymbols = {
            {1, "n."},
            {2, "v."},
            {3, "adj."},
            {4, "adv."},
            {5, "vt."},
            {6, "vi."},
            {7, "prep."},
            {8, "pron."},
            {9, "aux."},
            {10, "conj."},
            {11, "art."},
            {12, "int."},
            {13, "num."},
            {14, "c."},
            {15, "u."},
            {16, "s."},
            {17, "pl."}
    };

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
