//CLAUSE CHECK//Since 2014/6/17//Updated 2014/6/18 17:53
void ClauseCheck() {
	int r,r1,d=0;
	for(r=0; r<rwin; r++)
		if((WordSort(s[r].txt)==1||WordSort(s[r].txt)==8)
		        &&(strcmp(s[r+1].txt,"that")==0||SortEX(s[r+1].txt,"wh")==0)) {
			for(r1=r+1; r1<=rwin; r1++) if(strcmp(s[r1+1].txt,"/")==0) break;
			if(AskChar("Clause:��",s[r+1].txt,"��",s[r1].txt,"�õ�",s[r-d].txt,"ǰ?")==13)
				Words_Insert("Left",r-d,r+1,r1);
		}
}
