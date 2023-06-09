char WLTools(const std::string s) {
    popup(setModeYAutoIncrement);
    popup("#enableBorderTop=true;");
    popup("#offsetY=0;");
	popup("press [A] to add <ylw-blk>(", s, ")", 0);
    popup("press [R] to redirect <ylw-blk>(", s, ")", 0);
	popup("press [D] to delete <red-blk>(", s, ")", 0);
	popup("press [U] to update <cyn-blk>(", s, ")", 0);
    popup(setModeYIsConstant);

    const char choice = ::tolower(getch());
    char returnKey = 0;

	switch (choice) {
		case 'a':
            returnKey = addWord(s, AddMode::AddWord);
            break;
        case 'r':
            if (split(s, " ").size() == 1) {
                returnKey = addWord(s, AddMode::RedirectWord);
            } else {
                returnKey = addPhrase(s, AddMode::RedirectPhrase);
            }
            break;
		case 'd':
            if (split(s, " ").size() == 1) {
                returnKey = WordDelete(s);
            } else {
                returnKey = deletePhrase(s);
            }
            break;
		case 'u':
            returnKey = WordUpdate(s);
            break;
		default:
            errorLog("WLTools(s)", "option error");
            returnKey = 0;
            break;
	}
	return returnKey;
}
