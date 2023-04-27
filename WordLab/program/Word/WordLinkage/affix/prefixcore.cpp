int prefixcore(int lth,string &word,int affixmax,int affixlth,char affix[][8]) {
	for(int i=0; i<affixmax&&affix[i][0]!='#'&&strlen(affix[i])>0; i++) {
		if(word.find(affix[i])==0) {
			colorset(light|green);
			cout<<affix[i];
			if(lth-affixlth>0) {
				colorset(light|yellow);
				cout<<" + ";
			}
			for(int r=affixlth; r<lth; r++) word[r-affixlth]=word[r];
			lth-=affixlth;
			word.erase(lth);//exprimt'l
			// attention: word must be passed by reference not by value
		}
	}
	colorreset(lightwhite);
	return lth;
}
