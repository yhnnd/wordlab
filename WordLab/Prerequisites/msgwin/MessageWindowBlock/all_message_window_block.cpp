#include "defaults/all.cpp"
#include "adjust/all.cpp"
#include "fill/all.cpp"
#include "search/all.cpp"
#include "setnpl.cpp"
#include "Framework.cpp"
int messageBlocks::set(const int x, const int y, const int width, const int height, const int cleftIndex, const int numPerLine) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->cleftIndex = cleftIndex;
	this->numPerLine = numPerLine;
    return 0;
}

messageBlocks::messageBlocks(): x(0), y(0), cleftIndex(0), numPerLine(0), adjustWindowWidth(20), adjustWindowHeight(8) {

}
