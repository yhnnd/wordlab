std::string sortOfWord (const char *keyword, const set<int> preferedSortSymbols) {
    std::map<int, std::string> sorts = WordSort(keyword, preferedSortSymbols);
    std::string result = "";
    for (const auto item: sorts) {
        const int sortId = item.first;
        const string sortName = getWordSortNameById(sortId);
        if (sortName != "Unknown") {
            result += sortName + ", ";
        }
    }
    if (result.empty()) {
        return getWordSortNameById(0);
    } else {
        result.erase(result.find_last_not_of(", ") + 1);
    }
//    cout << "sorts.begin()->first = " << sorts.begin()->first << endl;
//    cout << "result = \"" + result + "\"" << endl;
	return result;
}

std::string sortOfWord (const char *keyword) {
    const set<int> availableSortIds = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
    return sortOfWord(keyword, availableSortIds);
}

set<int> sortIdsOfWord (const char * keyword) {
    const set<int> availableSortIds = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
    set<int> resultSet;
    std::map<int, std::string> sorts = WordSort(keyword, availableSortIds);
    for (const auto item: sorts) {
        resultSet.insert(item.first);
    }
    return resultSet;
}

std::string printableSortIdsOfWord (const char * keyword) {
    const set<int> resultSet = sortIdsOfWord(keyword);
    std::string result = "";
    for (const int sortId: resultSet) {
        result += toString(sortId) + ", ";
    }
    if (result.size()) {
        result.erase(result.find_last_not_of(", ") + 1);
    }
    return result;
}
