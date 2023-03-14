for(r=0; r<rwin; r++) {
	if(WordSort(s[r].txt)==1
	        &&WordSort(s[r+1].txt)==3
	        &&WordSort(s[r+2].txt)!=1
	        &&WordSort(s[r+2].txt)!=8)
		if(AskChar("WOC1-4<n.adj.>调换(",s[r].txt,")与(",s[r+1].txt,")?")==13) WordSwitch(r,r+1);
}
//更新时间 2014/6/18//n.+adj.//house big
