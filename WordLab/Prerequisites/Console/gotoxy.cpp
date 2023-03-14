void gotoxy(int x,int y){
#if defined(_WIN32)
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos={(short)x,(short)y};
	SetConsoleCursorPosition(hOut,pos);
#else
    move(x,y);
#endif
}
void gotoxy(COORD pos){
#if defined(_WIN32)
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos);
#else
    move(pos.X,pos.Y);
#endif
}
