int SortEX_NOUN(char s[]) { // 名词家族(大)
	if(
	    wordSortIncludes(s, {1, 8, 3, 4, 11})//n.//pron.//adj.//adv.//art.
	    && SortEX_WH(s) != 0
	) {
        return 0;
    }
	return -1;
}
