#include "setScreen.cpp"
#include "getxy.cpp"
#include "gotoxy.cpp"
#include "movexy.cpp"
#include "clearline.cpp"
#include "clearScreen.cpp"

#define recordxy(pos) const COORD pos = getxy()
#define resetxy(pos) gotoxy(pos.X, pos.Y)
