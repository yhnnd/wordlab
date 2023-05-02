#include "findverb.cpp"
#include "findnoun.cpp"
#include "findad.cpp"
#include "findaux.cpp"

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

int finderr(int r0,int *r1,const char * sort,const char * tool,const char * alias) {
	if(*r1==r0) {
		status(tool," finding ",alias," failed!");
	} else if(SortEX(s[*r1].txt,sort)) {
		status(tool," finding ",alias," error!");
		*r1 = r0;
	} else {
		status(tool," has found ",alias,"(",tostring(*r1),s[*r1].txt,")");
	}
    return 0;
}
