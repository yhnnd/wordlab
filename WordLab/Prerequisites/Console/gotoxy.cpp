void gotoxy(const COORD pos) {
#if defined(_WIN32)
    HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut,pos);
#elif defined(__APPLE__)
    printf("\033[%d;%dH", pos.Y + 1, pos.X);
    currentCursorPosition = pos;
//    move(pos.X, pos.Y);
#endif
}

void gotoxy(const int x, const int y) {
    COORD pos = {(short) x, (short) y};
    gotoxy(pos);
}