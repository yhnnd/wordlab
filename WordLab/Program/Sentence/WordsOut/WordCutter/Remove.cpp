void wordcutterremove(char *s,int n) {
	int r;
	if(n== 1) {
		for(r=0; s[r+2]; r++) s[r]=s[r+2];    //re *
		strclr(s,r);
	} else if(n== 2) {
		for(r=0; s[r+3]; r++) s[r]=s[r+3];    //dis *
		strclr(s,r);
	} else if(n== 9) {
		for(r=0; s[r+4]; r++) s[r]=s[r+4];    //anti *
		strclr(s,r);
	} else if(n==14) {
		for(r=0; s[r+2]; r++) s[r]=s[r+2];    //un *
		strclr(s,r);
	}
}
