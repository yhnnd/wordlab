int inputsuggests(char *suggests,char *msg,int lth,const COORD suggestionsWindowPos) {
	int i=0,n=1,r=0,msgbegin=0,maxresult=9;
	for(msgbegin=strlen(msg); msgbegin>0&&msg[msgbegin-1]!=' '; msgbegin--);
	char c;
	for(i=0; suggests[i]; i++) {
		c = suggests[i];
		if(c==',') n++;
		if(c==';') break;
	}
	char keywords[n][lth];
	for(i=0,n=0,r=0; suggests[i]; i++) {
		c = suggests[i];
		if(c==',') {
			strclr(keywords[n++],r);
			r=0;
			continue;
		}
		if(c==';') {
			strclr(keywords[n++],r);
			break;
		}
		keywords[n][r++] = c;
	}
	inputsuggestsshow(msg+msgbegin,&keywords[0][0],n,lth,maxresult, suggestionsWindowPos);
    return 0;
}
