void SWS1_6() {
	int r,r0,r1,r2,r3,r4;
	for(r0=0; r0<rwin; r0++)
		if((strcmp(s[r0].txt,"who")==0||strcmp(s[r0].txt,"where")==0)
		        &&(SortEX(s[r0+1].txt,"VERB")==0||(WordSort(s[r0+1].txt)==9&&SortEX(s[r0+2].txt,"VERB")!=0))
		  ) {
			seekverb(r0,&r1,rwin);
			finderr(r0,&r1,"verb","SWS1-6","verb1");
			seeknounEX(r1,&r2,rwin);
			finderr(r1,&r2,"noun","SWS1-6","noun1");
			seekverb(r2,&r3,rwin);
			finderr(r2,&r3,"verb","SWS1-6","verb2");
			seeknoun(r3,&r4,rwin);
			if(AskChar("SWS1-6A insert(",tostring(r1),s[r1].txt,")to(",tostring(r2),s[r2].txt,")?")==13)
				Word_Insert("Right",r1,r2);
			if(AskChar("SWS1-6B insert(",tostring(r0),s[r0].txt,")to(",tostring(r4),s[r4].txt,")?")==13)
				Word_Insert("Right",r0,r4);
			break;
		}
}
//include: who can i turn to? except: who can help me?
//Updated 2015.5.31
