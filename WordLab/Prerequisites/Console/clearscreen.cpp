void clearscreen(const int x,const int y,const int width,const int height,const char fill) {
	const auto cursorPosPrev = getxy();
	for (int r = 0; r < height; r++) {
	    gotoxy(x, y + r);
	    std::cout << std::setw(width) << std::setfill(fill) << "";
	}
	gotoxy(cursorPosPrev);
}
