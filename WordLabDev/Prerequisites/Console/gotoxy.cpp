void gotoxy(int x,int y){
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos={(short)x,(short)y};
	SetConsoleCursorPosition(hOut,pos);
}
void gotoxy(COORD pos){
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos);
}
