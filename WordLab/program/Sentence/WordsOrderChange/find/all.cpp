#include "findverb.cpp"
#include "findnoun.cpp"
#include "findad.cpp"
#include "findaux.cpp"
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
