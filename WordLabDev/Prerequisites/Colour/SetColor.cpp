BOOL colorset(WORD wAttributes){
	CurrentColor = wAttributes;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if( ColorL == false ) return SetConsoleTextAttribute(hConsole,15);//white
	return SetConsoleTextAttribute(hConsole, wAttributes);
}
BOOL colorreset(WORD color){
	return colorset(color);
}
WORD getcolor(){
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO Info;
    GetConsoleScreenBufferInfo(h, &Info);
    return Info.wAttributes;
}
