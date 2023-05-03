std::map<int, std::string> WordSortCore(const int lth, const int number, const set<int> preferredSortSymbols) {
	int NOL = 0;
    const int lineMaxChar = 256;
	char line[lineMaxChar];
	FILE * fp = Library(lth,CH,"r");

    std::map<int, std::string> result;

	while (!feof(fp)) {
		if (fgets(line, lineMaxChar, fp)) {
            NOL++;
        }
		if (NOL == number) {
			result = SortClassify(line, preferredSortSymbols);
			break;
		}
	}
	fclose(fp);
//    cout << "result.size = " << result.size() << endl;
	return result;
}
