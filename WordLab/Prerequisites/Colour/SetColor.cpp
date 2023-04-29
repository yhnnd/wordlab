#if defined(__APPLE__)
WORD current_color = lightwhite;
#endif

BOOL colorset(WORD wAttributes) {
#if defined(_WIN32)
	CurrentColor = wAttributes;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if( ColorL == false ) return SetConsoleTextAttribute(hConsole,15);//white
	return SetConsoleTextAttribute(hConsole, wAttributes);
#elif defined(__APPLE__)
    https://stackoverflow.com/questions/33309136/change-color-in-os-x-console-output/33311700
    current_color = wAttributes;
    const std::string color = get_mac_os_color_code(wAttributes);
    printf("\x1b[%sm", color.c_str());
#endif
    return 0;
}

BOOL colorreset(WORD color) {
	return colorset(color);
}

WORD getcolor() {
#if defined(_WIN32)
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO Info;
    GetConsoleScreenBufferInfo(h, &Info);
    return Info.wAttributes;
#elif defined(__APPLE__)
    return current_color;
#endif
}