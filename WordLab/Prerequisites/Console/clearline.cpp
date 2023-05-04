void clearline(const int x, const int y, const int lth, const char c) {
    int r;
    bool flag = (x >= 0 && y >= 0);

	if (flag) {
        gotoxy(x, y);
    }
    for (r = 0; r < lth; r++) {
        printf("%c", c);
    }

    if (flag) {
        gotoxy(x,y);
    } else {
        for (r = 0; r < lth; r++) {
            printf("\b");
        }
    }
}

void clearline(const int x, const int y) {
    clearline(x, y, ScreenX - 1, ' ');
}

void clearline(const int lth) {
    clearline(-1, -1, lth, ' ');
}