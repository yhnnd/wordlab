for(r=0; r<rwin-1; r++) {
	if(strcmp(s[r].txt,"when")==0&&SortEX(s[r+1].txt,"aux.")==0) {
		seeknoun(r+1,&r1,rwin);
		finderr(r+1,&r1,"noun","WOC1-8","noun1");
		if(AskChar("WOC1-8 ºóÖÃ(",s[r].txt,"-",s[r+1].txt,")µ½(",s[r1].txt,")ºó?")==13)
			Words_Insert("Right",r1,r,r+1);
		break;
	}
}
//Updated on 2014/6/18
//From: when + auxil. + n. + v.
//To:   n. + when + auxil. + v.
