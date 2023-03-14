//嚴格的查找模塊
void seekverb(int r0,int *r1,int rwin) {
	for(*r1=r0; *r1<rwin; ++*r1)
		if(SortEX(s[*r1].txt,"verb")==0&&SortEX(s[*r1+1].txt,"verb")!=0) break;
}
//不嚴格的查找模塊
void seekverbEX(int r0,int *r1,int rwin) {
	for(*r1=r0; *r1<rwin; ++*r1)
		if(SortEX(s[*r1].txt,"verb")==0||SortEX(s[*r1+1].txt,"verb")!=0) break;
}
