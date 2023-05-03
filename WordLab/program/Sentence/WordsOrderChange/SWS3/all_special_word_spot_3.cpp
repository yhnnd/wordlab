void sts::SpecialWordSpot3AdverbialClause() {
	int r0;
	for(r0 = 0; r0 < rwin; r0++ ) {
		if(strcmp(s[r0].txt,"now")==0||
		        strcmp(s[r0].txt,"today")==0||
		        strcmp(s[r0].txt,"yesterday")==0||
		        strcmp(s[r0].txt,"tomorrow")==0||
		        strcmp(s[r0].txt,"after")==0||
		        strcmp(s[r0].txt,"ago")==0||
		        strcmp(s[r0].txt,"before")==0
		  ) {
            const char ch = AskChar("SWS3-1前置",s[r0].txt,"?");
			if (ch == 13 || ch == 10) {
                Word_Insert("Left",0,r0);
            }
		}
	}
}
