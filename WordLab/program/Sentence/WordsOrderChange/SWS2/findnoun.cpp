void SWS2_FindNoun(int prepnumber) {
	int r;
	for(r=preppos0[prepnumber]+1; r<=rwin; r++)
		if((SortEX(s[r].txt,"REALNOUN")==0&&SortEX(s[r+1].txt,"REALNOUN")!=0)
		        ||(SortEX(s[r].txt,"NOUN")==0&&SortEX(s[r+1].txt,"NOUN")!=0)
		        ||(WordSort(s[r].txt)==1&&WordSort(s[r+1].txt)==11)
		        ||r==rwin) {
			preppos1[prepnumber]=r;
			break;
		}
}
