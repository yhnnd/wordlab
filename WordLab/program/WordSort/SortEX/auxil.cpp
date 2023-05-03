int SortEX_AUX(char *s) {
	if(wordSortIncludes(s, {9})//aux.
	        ||strcmp(s,"do")==0
	        ||strcmp(s,"did")==0
	        ||strcmp(s,"does")==0
	  ) {
        return 0;
    }
	return -1;
}
