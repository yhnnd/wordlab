int WordSort(const char *s) {
    const unsigned short delimLth = 1;
	char c[32];
	int sort = 0, r, k, km, lth = strlen(s);

	FILE *fp = Library(lth,EN,"r");

	int NOL = filelines(fp,false);

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
			sort = WordSortCore(lth,k);
			break;
		}
	}
	fclose(fp);
	return sort;
}
