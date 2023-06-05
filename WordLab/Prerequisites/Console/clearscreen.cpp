#ifdef _WIN32

int clearScreen() {
    return system("cls");
}

#elifdef __APPLE__

int clearScreen() {
    setColorByColorCode("97;40", "clearScreen", "setColorByColorCode");
    fflush(stdout);
    fflush(stdin);
    return system("clear");
}

#endif

void clearScreen(const int x, const int y, const int width, const int height, const char fill) {
	const auto cursorPosPrev = getxy();
	for (int r = 0; r < height; r++) {
	    gotoxy(x, y + r);
	    std::cout << std::setw(width) << std::setfill(fill) << "";
	}
	gotoxy(cursorPosPrev);
}
