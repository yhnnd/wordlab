int SortEX_AD(char *s) { //adj/adv.
	if((
	            WordSort(s)==3||//adj.
	            WordSort(s)==4//adv.
	        )&&SortEX_WH(s)!=0
	  )return 0;
	return -1;
}
