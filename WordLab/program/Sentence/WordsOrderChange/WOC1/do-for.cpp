for(r=0; r<rwin; r++) {
	if(
	    (WordSort(s[r].txt)==2
	     ||strcmp(s[r].txt,"do")==0
	     ||strcmp(s[r].txt,"did")==0
	     ||strcmp(s[r].txt,"does")==0
	    )
	    &&(SortEX(s[r].txt,"BE")!=0)
	    &&(strcmp(s[r+1].txt,"with")==0
	       ||strcmp(s[r+1].txt,"by")==0)
	) {
		for(r0=r+1; r0<=rwin-1; r0++)
			if(SortEX(s[r0+1].txt,"NOUN")!=0) break;
		if(AskChar("WOC1-1<v.prep.>将(",s[r].txt,")后置到(",s[r0].txt,")后?")==13)
			Word_Insert("Right",r,r0);
	}
}
