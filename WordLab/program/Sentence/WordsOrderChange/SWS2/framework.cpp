void SpecialWordSpot2Preposition() {
	int r,r0,r1;
	int specialmax = filelines(SpecialWordsRoute,true);
	if( specialmax <= 0 ) {
		popup("cannot find <red>(",SpecialWordsRoute,")",0);
		return;
	}
	char specialword[specialmax][30];
	int  specialpos[specialmax];
	loadmsg((char*)specialword,SpecialWordsRoute,specialmax,30,1,1);
	loadmsg((char*)preptrans0,PrepTrans0Route,maxprep,preplth,1,1);
	loadmsg((char*)preptrans1,PrepTrans1Route,maxprep,preplth,1,1);
	memset(specialpos,-1,sizeof(specialpos));
	memset(preppos0,-1,sizeof(preppos0));
	memset(preppos1,-1,sizeof(preppos1));
	for(r0=1; r0<=specialmax; r0++) {
		for(r=0; r<=rwin; r++) {
			if(strcmp(specialword[r0],s[r].txt)==0) {
				specialpos[r0]=r;
				break;
			}
		}
	}
	for(r=0; r<maxprep; r++) {
		r1 = SWS2_WordPos(r);
		if(specialpos[r1]>=0) {
			preppos0[r] = specialpos[r1];
			SWS2_FindNoun(r);
			popup("SWS2: prep <yellow>(",s[preppos0[r]].txt,") has been found.",0);
		}
	}
}
