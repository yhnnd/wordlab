void SWS1_7() {
	int r,r0,r1,r2,r3,r4;
	for(r0=0; r0<rwin; r0++) {
		if(SortEX(s[r0-1].txt,"wh")!=0&&SortEX(s[r0].txt,"BE")==0
		        &&WordSort(s[r0+1].txt)==8&&SortEX(s[r0+1].txt,"WH")!=0) {
			seeknounEX(r0,&r1,rwin);
			finderr(r0,&r1,"noun","SWS1-7","noun1");
			if(AskChar("SWS1-7A right insert",tostring(r0),s[r0].txt,"to",tostring(r1),s[r1].txt,"?")==13)
				Word_Insert("Right",r0,r1);
			if(AskChar("SWS1-7B left insert",tostring(r0),s[r0].txt,"-",tostring(r1),s[r1].txt,"?")==13)
				Words_Insert("Left",0,r0,r1);
			break;
		}
	}
}
