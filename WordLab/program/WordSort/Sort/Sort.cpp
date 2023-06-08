std::map<int, std::string> WordSort(const char *s, const set<int> preferredSortSymbols) {
    const unsigned short delimLth = 1;
	char c[32];
	int r, k, km, lth = strlen(s);

    std::map<int, std::string> result;

	FILE *fp = Library(lth,EN,"r");

	int NOL = fileLines(fp, false);

	for (k = 1; k <= NOL; k++) {

		fseek(fp, (k - 1) * (lth + delimLth), 0);
		fread(&c, lth, 1, fp);
		rewind(fp);

		for(km = 0, r = 0; r < lth; r++) {
            if (s[r] == c[r]) {
                km = km + 1;
            }
        }
		if (km == lth) {
			result = WordSortCore(lth, k, preferredSortSymbols);
			break;
		}
	}
	fclose(fp);
	return result;
}

int wordSortIncludes(const char * word, const set<int> preferredSortIds) {
    return WordSort(word, preferredSortIds).size();
}

std::map<int, std::string> wordSort(const char * word) {
    return WordSort(word, availableSortIds);
}

bool wordSortIsNoType(const char * word) {
    return wordSort(word).size() == 0;
}