#include "setscreen.cpp"
#include "getxy.cpp"
#include "gotoxy.cpp"
#include "gotoxymove.cpp"
#include "clearline.cpp"
#include "clearscreen.cpp"

#define cursormove(x,y) gotoxymove(1,x,0,y)
#define recordxy(pos) COORD pos = getxy()
#define resetxy(pos) gotoxy(pos.X,pos.Y)
