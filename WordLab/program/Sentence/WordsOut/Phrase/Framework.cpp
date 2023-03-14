int PhrasesChecker(int rwout,int rwin,int Limit) {
	int r;
	FILE *fp;
	char PhraseRoute[30];
	for(r=maxlen; r>=0; r--) {
		if(r<=Limit) {
			strcpy(PhraseRoute,PhraseRouteA);
			strcat(PhraseRoute,tostring(r).c_str());
			strcat(PhraseRoute,PhraseRouteB);
			fp=fopen(PhraseRoute,"r");
			if(PhrasesCheckerCore(rwout,rwin,r,fp)) return r;
		}
	}
	return 0;
}
