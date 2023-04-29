void gotoxy(COORD pos) {
#if defined(_WIN32)
    HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut,pos);
#elif defined(__APPLE__)
    printf("\033[%d;%dH", pos.Y, pos.X);
//    move(pos.X, pos.Y);
#endif
}

void gotoxy(int x, int y) {
    COORD pos={(short)x, (short)y};
    gotoxy(pos);
}