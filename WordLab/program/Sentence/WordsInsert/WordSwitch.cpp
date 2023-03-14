void WordSwitch(int sub1,int sub2) {
	int r;
	char sub=0;
	for(r=0; r<=29; r++) {
		sub=s[sub1].txt[r];
		s[sub1].txt[r]=s[sub2].txt[r];
		s[sub2].txt[r]=sub;
	}
}
