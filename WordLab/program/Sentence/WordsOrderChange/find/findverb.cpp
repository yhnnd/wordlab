//����Ĳ���ģ�K
void seekverb(int r0,int *r1,int rwin) {
	for(*r1=r0; *r1<rwin; ++*r1)
		if(SortEX(s[*r1].txt,"verb")==0&&SortEX(s[*r1+1].txt,"verb")!=0) break;
}
//������Ĳ���ģ�K
void seekverbEX(int r0,int *r1,int rwin) {
	for(*r1=r0; *r1<rwin; ++*r1)
		if(SortEX(s[*r1].txt,"verb")==0||SortEX(s[*r1+1].txt,"verb")!=0) break;
}
