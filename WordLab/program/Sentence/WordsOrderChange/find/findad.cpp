//如果此單詞不符, 繼續依次查找
//如果此單詞符合, 下一個單詞也符合, 繼續依次查找
void seekad(int r0,int *r1,int rwin){
	for(*r1=r0;*r1<rwin;++*r1)
		if(SortEX(s[*r1+1].txt,"ad.")!=0) break;
}
//如果此單詞不符, 繼續依次查找
//如果此單詞符合, 下一個單詞也符合, 停止查找
void seekadEX(int r0,int *r1,int rwin){
	for(*r1=r0;*r1<rwin;++*r1)
		if(SortEX(s[*r1+1].txt,"ad.")!=0) break;
}
//如果此單詞不符, 停止查找
//如果此單詞符合, 下一個單詞也符合, 繼續依次查找
void skipad(int r0,int *r1,int rwin){
	for(*r1=r0;*r1<rwin;++*r1)
		if(SortEX(s[*r1+1].txt,"ad.")!=0) break;
}
//如果此單詞不符, 停止查找
//如果此單詞符合, 下一個單詞也符合, 停止查找
void skipadEX(int r0,int *r1,int rwin){
	for(*r1=r0;*r1<rwin;++*r1)
		if(SortEX(s[*r1+1].txt,"ad.")!=0) break;
}
