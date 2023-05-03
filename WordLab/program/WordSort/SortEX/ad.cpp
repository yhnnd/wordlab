int SortEX_AD(char *s) { // adj / adv.
	if(
            wordSortIncludes(s, {3, 4})//adj. //adv.
	        && SortEX_WH(s)!=0
	  ) {
        return 0;
    }
	return -1;
}
