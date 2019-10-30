int SortEX_DefinitelyNOUN(char s[]) { //名词家族(小)
	if(
	    WordSort(s)==1||//n.
	    WordSort(s)==3||//adj.
	    WordSort(s)==11//art.
	)return 0;
	return -1;
}
