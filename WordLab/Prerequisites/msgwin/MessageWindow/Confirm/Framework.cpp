int MessageWindow::Confirm(const int n, const int x, const int y, const int windowWidth, const char *what, const int max, const int lineWidth) {
    int r = 0;
    const int actualMax = MaxLength(what, max, lineWidth);
    recordxy(xy);
	bool background = SetBackground(1),monochrome = SetMonochrome(1);
    Frame(0, x, y, windowWidth, what, actualMax, lineWidth);
//    printf("frame was printed\n");
    r = ConfirmSwitch(n,x+1,y+actualMax-1, windowWidth + 5, 2);
    Frame(-1, x, y, windowWidth, actualMax, actualMax);
	SetMonochrome(monochrome);
	SetBackground(background);
    resetxy(xy);
    return r;
}
