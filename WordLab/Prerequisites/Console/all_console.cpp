#include "setscreen.cpp"
#include "getxy.cpp"
#include "gotoxy.cpp"
#include "movexy.cpp"
#include "clearline.cpp"
#include "clearscreen.cpp"

#define recordxy(pos) const COORD pos = getxy()
#define resetxy(pos) gotoxy(pos.X, pos.Y)
