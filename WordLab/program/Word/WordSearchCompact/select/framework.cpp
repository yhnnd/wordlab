int Select(const char keyword[],char wordbase[],int x,int y) {
	int n_match = 0, row_max = 5, full = -1;
	float substrRatio = 0.5, subseqRatio = 0.5;
	set<string> matched;
	FILE * fp = fopen(EnglishRoute,"r");
	rewind(fp);
	while(true) {
		if(SelectLoad(wordbase,fp)==-1) break;
		if(SelectSubstr(wordbase,keyword,substrRatio)) {
			n_match = SelectReport(wordbase,n_match,x,y,row_max,full);
			if( n_match == full ) break;
			matched.insert(wordbase);
		}
	}
	if( n_match != full ) {
		rewind(fp);
		while(true) {
			if(SelectLoad(wordbase,fp)==-1) break;
			if(SelectSubseq(wordbase,keyword,subseqRatio)) {
				if( matched.find(wordbase) != matched.end() ) continue;
				n_match = SelectReport(wordbase,n_match,x,y,row_max,full);
				if( n_match == full ) break;
				matched.insert(wordbase);
			}
		}
	}
	fclose(fp);
	return n_match;
}
