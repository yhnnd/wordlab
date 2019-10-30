#include "defaults\\all.cpp"
#include "adjust\\all.cpp"
#include "fill\\all.cpp"
#include "search\\all.cpp"
#include "setnpl.cpp"
#include "Framework.cpp"
messageblock::set(int x,int y,int width,int height,int cleftindex,int npl){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->cleftindex = cleftindex;
	this->npl = npl;
}
messageblock::messageblock():x(0),y(0),cleftindex(0),npl(0),aww(20),awh(8){
}
