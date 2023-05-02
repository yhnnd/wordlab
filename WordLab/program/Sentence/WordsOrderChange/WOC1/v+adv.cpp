for(r=0; r<rwin; r++) {
	if(SortEX(s[r-1].txt,"VERB")==0 && WordSort(s[r].txt)==4 && strcmp(s[r].txt,"how") != 0
    &&SortEX(s[r+1].txt,"VERB")!=0&&WordSort(s[r+1].txt)!=3) {
		if(AskChar("WOC1-5<v.adv.>调换(",s[r-1].txt,")与(",s[r].txt,")?")==13) {
            WordSwitch(r-1,r);
        }
    }
}
//更新时间 2014/6/19//v.+adv.
