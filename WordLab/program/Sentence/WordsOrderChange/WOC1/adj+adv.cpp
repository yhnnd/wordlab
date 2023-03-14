//更新时间 2015/10/29//adj.+adv.
for(r=0; r<rwin; r++) {
	if(WordSort(s[r-1].txt)==3
	        &&WordSort(s[r].txt)==4&&strcmp(s[r].txt,"how")!=0
	        &&WordSort(s[r+1].txt)!=3) {
		if(AskChar("WOC1-9<adj.adv.>调换(",s[r-1].txt,")与(",s[r].txt,")?")==13)
			WordSwitch(r-1,r);
	}
}
