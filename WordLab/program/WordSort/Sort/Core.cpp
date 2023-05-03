int WordSortCore(int lth, int number) {
	int NOL = 0, sort = 0;
    const int lineMaxChar = 256;
	char c[lineMaxChar];
	FILE * fp = Library(lth,CH,"r");
	while (!feof(fp)) {
		if (fgets(c, lineMaxChar, fp)) {
            NOL++;
        }
		if (NOL == number) {
			sort = SortClassify(c);
			break;
		}
	}
	fclose(fp);
	return sort;
}
