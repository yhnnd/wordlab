int SortEX_DefinitelyNOUN(char s[]) { //名词家族(小)
	if (
            wordSortIncludes(s, {1, 3, 11})//n.//adj.//art.
	) {
        return 0;
    }
	return -1;
}
