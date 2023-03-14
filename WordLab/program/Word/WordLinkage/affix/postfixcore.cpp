int postfixcore(int lth,string &word,int affixmax,char affix[][22][10],int lthmax) {
	for(int j=lthmax; j>0; j--) {
		if(lth>=j) {
			for(int i=0; i<affixmax&&affix[j-1][i][0]!='#'&&strlen(affix[j-1][i])>0; i++) {
				if(lth-j>=0&&
				        word.substr(lth-j)==affix[j-1][i]//exprimt'l
				  ) {
					if((lth-=j)>0) {
						word.erase(lth);//exprimt'l
						postfixcore(lth,word,affixmax,affix,lthmax);
						colorset(light|yellow);
						cout<<" + ";
					}
					colorset(light|cyan);
					cout<<affix[j-1][i];
					colorreset(white);
					return lth;
				}
			}
		}
	}
	return infix(lth,word);
}
