void SWS1_8() {
	int r,r0,r1,r2,r3,r4;
	for(r0=0; r0<rwin; r0++) {
		if(strcmp(s[r0].txt,"whose")==0) {
			seeknounEX(r0,&r1,rwin);
			finderr(r0,&r1,"noun","SWS1-8","noun1");
			seekverb(r1,&r2,rwin);
			finderr(r1,&r2,"verb","SWS1-8","verb1");
			seeknounEX(r2,&r3,rwin);
			finderr(r2,&r3,"noun","SWS1-8","noun2");
			if(AskChar("SWS1-8-v.insert",s[r2].txt,"to",s[r3].txt,"?")==13)
				Word_Insert("Right",r2,r3);
			if(AskChar("SWS1-8-n.insert",s[r0].txt,"-",s[r1].txt,"to",s[r3].txt,"?")==13)
				Words_Insert("Right",r3,r0,r1);
		}
	}
}
//¸üÐÂ•rég 2014/6/17
