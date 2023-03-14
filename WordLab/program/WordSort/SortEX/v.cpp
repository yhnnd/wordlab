int SortEX_VERB(char *s) {
	if(
	    WordSort(s)==2||//verb
	    WordSort(s)==5||//vt.
	    WordSort(s)==6||//vi.
	    strcmp(s,"do")==0
	)return 0;
	return -1;
}
