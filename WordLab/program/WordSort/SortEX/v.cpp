int SortEX_VERB(char *s) {
	if(
	    wordSortIncludes(s, {2, 5, 6})||//verb //vt. //vi.
	    strcmp(s,"do")==0
	) {
        return 0;
    }
	return -1;
}
