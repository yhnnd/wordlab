//
void seekaux(int r0,int *r1,int rwin) {
	for(*r1=r0; *r1<rwin; ++*r1)
		if(SortEX(s[*r1+1].txt,"aux.")!=0) break;
}
//
void skipaux(int r0,int *r1,int rwin) {
	for(*r1=r0; *r1<rwin; ++*r1)
		if(SortEX(s[*r1].txt,"aux.")!=0) break;
}
