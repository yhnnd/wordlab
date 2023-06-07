int WLFramework(void) {
    char FirstLetter = 0;
    std::string inputText = "", prevInputText = "";
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
            char * inputChars = (char *) calloc(64, sizeof(char));
			if (isalpha(FirstLetter)) {
                inputChars[0] = FirstLetter;
                index(inputChars, 10, 9, lightgreen, 1);
            } else {
                index(inputChars, 10, 9, lightgreen, 0);
            }

			FirstLetter = 0;

            inputText = trim(inputChars).c_str();
            free(inputChars);

            if (inputText == "#") {
                // Restore Previous Input Text
                inputText = prevInputText;
            } else if (inputText == "##") {
                // Options for Previous Input Text
                inputText = prevInputText + "#";
            } else {
                // Record Input Text
                prevInputText = replace(inputText, "#", "");
            }
		}
		// PROCESS DATA
		const std::string::size_type tokenPosition = inputText.find("#");
        if (tokenPosition != std::string::npos) {
            inputText = replace(inputText, "#", "");// remove '#'
			FirstLetter = WLTools(inputText);
		} else if (inputText.find(" ") != std::string::npos) {
			if (!WLSearchPhrase(inputText, true) && CL) {
                FirstLetter = AddNew(inputText);
            }
		} else if (inputText.empty() == true || inputText.length() > 30) {
            return -1;
        } else {
			const int BeginY = 5;
            clearScreen(0, BeginY, ScreenX, ScreenY - 1 - BeginY);
			gotoxy(0, BeginY);
			FirstLetter = WLFrameworkCore(inputText);
            if (FirstLetter == 0) {
                gotoxy(0, BeginY + 3);
                FirstLetter = WLDictionary(inputText);
            }
			if (FirstLetter == 8/* backspace */ || FirstLetter ==127/* delete */ || FirstLetter == 27/* escape */) {
                return -1;
            }
		}
	}
    return 0;
}
