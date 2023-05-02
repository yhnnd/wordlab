COORD getxy(){
#if defined(_WIN32)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(hConsole, &csbi)){
		return csbi.dwCursorPosition;
	}
#elif defined(__APPLE__)
    FILE * fpw = freopen("stdout", "w", stdout);
    system("echo -e '\033[6n'");

    char * buffer;
    size_t bufsize = 32;
    size_t lth = 0;
    buffer = (char *) malloc (bufsize * sizeof(char));
    memset(buffer, 0, bufsize * sizeof(char));
    FILE * fpr = fopen("stdout", "r");
    lth = getline(&buffer, &bufsize, fpr);
    fclose(fpr);
    fclose(fpw);
    system("rm stdout");
    freopen("/dev/tty", "w", stdout);
    std::string buffer2 = "";
    int i, i2;/* [6;42R */
    for (i = 0, i2 = 0; i < lth; ++i) {
        if (isprint(buffer[i])) {
            buffer2 += buffer[i];
        } else {
            char s[8];
            snprintf(s, 8, "%d", buffer[i]);
            buffer2 += s;
        }
    }
    free(buffer);
    int begin, end;
    for (begin = 0; begin < buffer2.length(); ++begin) {

    }
//    printf("\nlth = %zu, buffer2 = \"%s\"\n" , lth, buffer2.c_str());
//    getch();
    return currentCursorPosition;
#endif
}
