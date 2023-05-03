int SortEX_REALNOUN(char s[]) { //名词家族(中)
	if (
            wordSortIncludes(s, {1, 8, 3, 11})//n.//pron.//adj.//art.
	        && SortEX_WH(s)!=0
	) {
        return 0;
    }
	return -1;
}
