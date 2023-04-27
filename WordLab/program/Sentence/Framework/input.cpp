char Input(int x,int y) {
	int r;
	char c;
	for(r=0,c=0,strclr(s[rwin].txt);; r++) {
	begin:
		colorset(lightwhite);
		c = getche();
		if(c==8) {
			cout<<" \b";
			c = 0;
			punct = 0;
			if( r > 0 ) {
				s[rwin].txt[--r]=0;
			} else if(rwin) {
				strclr(s[rwin].txt);
				r = strlen(s[--rwin].txt);
				FrameworkCore(x,y);
			} else break;
			indexCore(s[rwin].txt,12,8,green);
			goto begin;
		} else if(c=='#'||c=='@') {
			cout<<"\b";
			WordSortSelect(s[rwin]);
			r--;
		} else if(c==' '||c==','||c==';'||c=='.'||c=='?'||c=='!'||c==13||c==0) break;
		else if( c > 0 ) s[rwin].txt[r] = c;
		indexCore(s[rwin].txt,12,8,green);
	}
	strclr(s[rwin].txt,r);
	return (c==','||c==';'||c=='.'||c=='?'||c=='!'||c==13||c==0) ? c : ' ';
}
