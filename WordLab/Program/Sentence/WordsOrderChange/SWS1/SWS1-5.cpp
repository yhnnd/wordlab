void SWS1_5() {
	int r,r0,r1,r2,r3,r4;
	for(r0=0; r0<rwin; r0++)
		if(SortEX(s[r0].txt,"wh")==0&&(strcmp(s[r0].txt,"what")==0||strcmp(s[r0].txt,"which")==0)) {
			seeknoun(r0,&r1,rwin);
			finderr(r0,&r1,"noun","SWS1-5","noun1");
			seekverb(r1,&r2,rwin);
			finderr(r1,&r2,"verb","SWS1-5","verb1");
			seeknounEX(r2,&r3,rwin);
			finderr(r2,&r3,"noun","SWS1-5","noun2");
			seekverb(r3,&r4,rwin);
			finderr(r3,&r4,"verb","SWS1-5","verb2");
			if(AskChar("SWS1-5-v.insert(",s[r2].txt,")to(",s[r3].txt,")?")==13)
				Word_Insert("Right",r2,r3);
			if(AskChar("SWS1-5-n.insert(",s[r0].txt,"-",s[r1].txt,")to(",s[r4].txt,")?")==13)
				Words_Insert("Right",r4,r0,r1);
			break;
		}
}
