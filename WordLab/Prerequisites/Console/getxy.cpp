COORD getxy(){
#if defined(_WIN32)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(hConsole, &csbi)){
		return csbi.dwCursorPosition;
	}
#endif
    return {0,0};
}
