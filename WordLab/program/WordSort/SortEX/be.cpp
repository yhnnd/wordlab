int SortEX_BE(char *s) {
	if(strcmp(s,"am")==0
	        ||strcmp(s,"is")==0
	        ||strcmp(s,"was")==0
	        ||strcmp(s,"are")==0
	        ||strcmp(s,"were")==0
	        ||strcmp(s,"be")==0
	        ||strcmp(s,"been")==0
	  ) {
        return 0;
    }
	return -1;
}
