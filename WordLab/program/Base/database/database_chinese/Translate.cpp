std::string Translation(const std::string word, int definitionNumber) {
	const int lth = word.length();
	const int pos = Search(word.c_str(), lth, false);
    if (pos > 0) {
        const auto definitionsVector = getWordDefinitions(lth, pos);
        if (definitionsVector.size()) {
            if (definitionNumber >= 0 && definitionNumber < definitionsVector.size()) {
                return definitionsVector[definitionNumber].text;
            }
        }
    }
    return word;
}
// updated on 1st May 2017
// updated on Fri Jun 9 2023
