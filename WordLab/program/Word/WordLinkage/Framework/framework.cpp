int WLFramework(void) {
	int lth = 0;
    char s[32] = "", FirstLetter = 0;
	if (VL and db_is_secure(false, true) == false) {
        getch();
    }
	if (CType == 0) {
        const char ch = popup("<-wte>(Add word Engine Authorization Was Set Off. Reset now?", -1);
		if (ch == KEY_CARRIAGE_RETURN || ch == KEY_NEW_LINE) {
            CType = 1;
		}
	}

	clearScreen();
    setForegroundColorAndBackgroundColor("wte-", "-blk");

	for (;;) {
        // INPUT DATA
		if (FirstLetter != 13 && FirstLetter != 10) {
			memset(s, 0, sizeof(s));
			if (isalpha(FirstLetter)) {
                s[0] = FirstLetter;
                index(s, 10, 9, lightgreen, 1);
            } else {
                index(s, 10, 9, lightgreen, 0);
            }

			FirstLetter = 0;

            strcpy(s, trim(s).c_str());
			lth = strlen(s);
		}
		// PROCESS DATA
		char * ptr_token = strstr(s, "#");
		if (ptr_token != nullptr) {
			(*ptr_token) = 0;// remove #
			if (*(ptr_token + 1) != '\0') {
                strcpy(ptr_token, ptr_token + 1);
            }
			// re-order the word after removing #
			FirstLetter = WLTools(s);
		} else if (strindex(s, " ") >= 0) {
			if (!WLSearchPhrase(s) && CL) {
                FirstLetter = AddNew(s);
            }
		} else if (lth <= 0 || lth > 30) {
            return -1;
        } else {
			const int BeginY = 5;
            clearScreen(0, BeginY, ScreenX, ScreenY - 1 - BeginY);
			gotoxy(0, BeginY);
			FirstLetter = WLFrameworkCore(s);
            if (FirstLetter == 0) {
                gotoxy(0, BeginY + 3);
                FirstLetter = WLDictionary(s);
            }
			if (FirstLetter == 8/* backspace */ || FirstLetter ==127/* delete */ || FirstLetter == 27/* escape */) {
                return -1;
            }
		}
	}
    return 0;
}
