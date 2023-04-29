void popupSafe (const char * msg, const char * var1 = NULL, const char * var2 = NULL, const char * var3 = NULL) {
    const int indentLeft = 5;
    const int marginTop = 1;
    const char * bar = "+----------------------------------------------------------------------+";
    const int maxWidth = strlen(bar);
    colorrecord(colorPrev);
    if (strcmp(msg, "#clear") == 0) {
        colorsetcmd("wte-");
        for (int r = 0; r < 3; ++ r) {
            gotoxy(indentLeft, marginTop + r);
            for (int i = 0; i < maxWidth + 2; ++i) {
                fputc(' ', stdout);
            }
        }
    } else {
        char s [64] = "";
        snprintf(s, 64, msg, var1, var2, var3);
        // Border Top
        gotoxy(indentLeft, marginTop);
        colorsetcmd("blu-blu");
        printf(" %s ", bar);
        // Border Left
        gotoxy(indentLeft, marginTop + 1);
        printf(" |");
        // Background
        colorsetcmd("-wte");
        printf("%70s", "");
        // Border Right
        colorsetcmd("blu-blu");
        printf("| ");
        // Content
        gotoxy(indentLeft + 2, marginTop + 1);
        colorsetcmd("-wte");
        printf(" %s ", s);
        // Border Bottom
        gotoxy(indentLeft, marginTop + 2);
        colorsetcmd("blu-blu");
        printf(" %s ", bar);
    }
    colorreset(colorPrev);
}

window::INPUT_STATUS window::inputcore(int& x0,int& y0,int& x,int& y) {
	char * msg = text.line(y);
	char CHAR;
	bool REFRESH_PAGE = false;
	while(x>=0&&x<text.linecapacity()){
		// REFRESH PAGE
		if(x<=x0){
			x0 = x/innerWidth()*innerWidth();
			REFRESH_PAGE = true;
		}
		if(x>x0+innerWidth()){
			x0 += innerWidth();
			REFRESH_PAGE = true;
		}
		if(REFRESH_PAGE){
			Reader(WINDOW_STATUS::active,x0,y0,0);
			REFRESH_PAGE = false;
		}
		refresh(x0,y0,x,y);// REFRESH LINE
		// GET CHAR
		CHAR = getch();

	    if (CHAR == 27 || CHAR == MAC_OS_BIOSKEY_1) {//ESC
#if defined(__APPLE__)
//            printf("\nchar 3 is = '%c' %d\n", CHAR, CHAR);
            popupSafe("press %s or %s or %s to quit.", "[ESC]", "[ENTER]", "[↑] [↓] [←] [→]");
            CHAR = getch();
            if (CHAR == 27 || CHAR == 13) {
                return INPUT_STATUS::ESCAPE;
            } else {
                popupSafe("#clear");
                if (CHAR == MAC_OS_BIOSKEY_2) {
                    CHAR = getch();
                    switch (CHAR) {
                        case MAC_OS_UP: return INPUT_STATUS::Up;
                        case MAC_OS_DOWN: return INPUT_STATUS::Down;
                        case MAC_OS_LEFT: return INPUT_STATUS::Left;
                        case MAC_OS_RIGHT: return INPUT_STATUS::Right;
                        default: return INPUT_STATUS::UNKNOWN_BIOSKEY;
                    }
                }
            }
#elif defined(_WIN32)
	    	return INPUT_STATUS::ESCAPE;
#endif
	    } else if (CHAR == 13) {// NEW LINE
			return INPUT_STATUS::NEW_LINE;
		} else if (CHAR == 8 || CHAR == 127) {// DELETE
			if (x > 0) {
				for (int i=--x; i < text.length(y); ++i) {
                    msg[i] = msg[i+1];
                }
				continue;
			} else {
                return INPUT_STATUS::DELETE_LINE;
            }
		} else if (CHAR == -32) {// BIOSKEY
			CHAR = getch();
			switch (CHAR) {
				case UP: return INPUT_STATUS::Up;
				case DOWN: return INPUT_STATUS::Down;
				case LEFT: return INPUT_STATUS::Left;
				case RIGHT: return INPUT_STATUS::Right;
				default: return INPUT_STATUS::UNKNOWN_BIOSKEY;
			}
		} else if(CHAR=='\t') {//TABLE
			x+=3;
			strcat(msg,"    ");
			continue;
		} else {

        }
		msg[text.length(y)+1] = 0;
		for(int i=text.length(y);i>x;--i) msg[i] = msg[i-1];
		msg[x++] = CHAR;
	}
	return INPUT_STATUS::OUT_OF_LINE;
}
