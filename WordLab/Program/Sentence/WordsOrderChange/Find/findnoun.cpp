//如果此單詞不符合, 繼續依次查找
//如果此單詞符合, 下一個單詞也符合, 繼續依次查找
void seeknoun(int r0,int *r1,int rwin) {
	for(*r1=r0; *r1<rwin; ++(*r1))
		if((SortEX(s[*r1].txt,"noun")==0&&SortEX(s[*r1+1].txt,"REALNOUN")!=0)
		        ||SortEX(s[*r1+1].txt,"noun")!=0) break;
}
//如果此單詞不符合, 繼續依次查找
//如果此單詞符合, 下一個單詞也符合, 停止查找
void seeknounEX(int r0,int *r1,int rwin) {
	for(*r1=r0; *r1<rwin; ++(*r1))
		if((SortEX(s[*r1].txt,"NOUN")==0&&SortEX(s[*r1+1].txt,"REALNOUN")!=0)
		        ||(WordSort(s[*r1].txt)==1&&WordSort(s[*r1+1].txt)!=1)
		        ||(WordSort(s[*r1].txt)==8&&WordSort(s[*r1+1].txt)==8)
		  )break;
}
//如果此單詞不符, 停止查找
//如果此單詞符合, 下一個單詞也符合, 繼續依次查找
void skipnoun(int r0,int *r1,int rwin) {
	for(*r1=r0; *r1<rwin; ++(*r1))
		if(SortEX(s[*r1].txt,"noun")!=0) break;
}
