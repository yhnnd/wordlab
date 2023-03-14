void ConjCheck() {
	int r,r1;
	for(r=0; r<rwin; r++) {
		if(
		    strcmp(s[r].txt,"if")==0||
		    strcmp(s[r].txt,"because")==0||
		    strcmp(s[r].txt,"except")==0||
		    strcmp(s[r].txt,"despite")==0||
		    strcmp(s[r].txt,"exclude")==0||
		    strcmp(s[r].txt,"though")==0||
		    strcmp(s[r].txt,"although")==0) {
			for(r1=r; r1<=rwin; r1++) if(strcmp(s[r1+1].txt,"/")==0) break;
			if(AskChar("Conj:将",s[r].txt,"到",s[r1].txt,"前置?")==13) {
				Words_Insert("Left",0,r,r1);
				break;
			}
		}
	}
}
//Conjunction Checker//Since 2014/6/16//更新时间 2014/6/17
