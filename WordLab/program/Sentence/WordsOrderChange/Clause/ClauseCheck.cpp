//CLAUSE CHECK//Since 2014/6/17//Updated 2014/6/18 17:53
void sts::ClauseCheck() {
	int r, r1, d=0;
	for (r=0; r<rwin; r++) {
        if((WordSort(s[r].txt)==1||WordSort(s[r].txt)==8)
           &&(strcmp(s[r+1].txt,"that")==0||SortEX(s[r+1].txt,"wh")==0)) {
            for (r1=r+1; r1<=rwin; r1++) {
                if(strcmp(s[r1+1].txt,"/")==0) {
                    break;
                }
            }
            if (AskChar("Clause:将",s[r+1].txt,"到",s[r1].txt,"置到",s[r-d].txt,"前?")==13) {
                Words_Insert("Left",r-d,r+1,r1);
            }
        }
    }
}
