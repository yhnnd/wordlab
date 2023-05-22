void toggles::toggle::showToggle(int x, int y, bool lock, bool delay, bool showDigit) {
    recordxy(pos);
    colorrecord(colorprev);

    int r = (delay) ? 0 : 3;

    for (; r <= 3; r++) {
        gotoxy(x,y);
        colorset(backlight|backgreen);
        std::cout<<"   ";

        gotoxy(x + 3,y);
        colorset(backlight|backred);
        std::cout<<"   ";

        if (lock) {
            gotoxy(x + r, y);
        } else {
            gotoxy(x + 3 -r, y);
        }

        if (showDigit) {
            colorset(backlightwhite);
        } else {
            colorset(bothlightwhite);
        }

        std::cout<<"   ";
    }
    std::cout<<"\b\b" << lock;
    colorreset(colorprev);
    resetxy(pos);
}


void toggles::toggle::toggleToggle(const int x, const int y, bool *lock, const bool delay, const bool showDigit) {
    deny(*lock, *lock);
    toggles::toggle::showToggle(x, y, *lock, delay, showDigit);
}


inline int toggles::getLeft(const int x, const int width) {
    int left = x + width;
#ifdef __APPLE__
    if (x > 0) {
        left += -1;
    }
#endif
    return left;
}


void toggles::showAll(const int x, const int y, const int width, const bool showDigit, const int n, ...) {

    const int left = toggles::getLeft(x, width);

    va_list argv;
    va_start(argv, n);
    for (int r = 1; r <= n; r++) {
        toggles::toggle::showToggle(left, y + 1 + r, va_arg(argv, int), false, showDigit);
    }
    va_end(argv);
}


// r is the NO. of the toggle, n is the maximum of toggles
void toggles::toggle(const int x, const int y, const int width, const bool showDigit, const int r, const int n, ...) {
    if (r < 0 || r > n) {
        return;
    }
    bool * flagPtr = nullptr;
    va_list argv;
    va_start(argv,n);
    for(int i = 1; i <= r && i <= n; i++) {
        flagPtr = va_arg(argv,bool *);
    }
    va_end(argv);

    const int left = toggles::getLeft(x, width);

    toggles::toggle::toggleToggle(left, y + 1 + r, flagPtr, true, showDigit);
}
