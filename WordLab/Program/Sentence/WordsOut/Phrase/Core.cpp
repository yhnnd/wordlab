int PhrasesCheckerCore(int rwout,int rwin,int len,FILE *fp) {
	int i=0,r=0,flag=0;
	char ch,S[maxlen+1][30];
	rewind(fp);
	memset(S,0,sizeof(S));
	while((ch=getc(fp))!=EOF) {
		if(ch== ',') {
			flag++;
			r=0;
			continue;
		} else if(ch== ';') {
			if((i=PhraseCheckerCoreKernel(len,S))) break;
			continue;
		} else if(ch=='\n') {
			flag=0;
			memset(S,0,sizeof(S));
			continue;
		} else S[flag-1][r++]=ch;
	}
	fclose(fp);
	return i;
}
