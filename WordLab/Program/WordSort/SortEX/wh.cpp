int SortEX_WH(char s[]) {
	if(strcmp(s,"what")==0
	        ||strcmp(s,"which")==0
	        ||strcmp(s,"when")==0
	        ||strcmp(s,"where")==0
	        ||strcmp(s,"who")==0
	        ||strcmp(s,"whom")==0
	        ||strcmp(s,"whose")==0
	        ||strcmp(s,"how")==0
	  )return 0;
	return -1;
}
