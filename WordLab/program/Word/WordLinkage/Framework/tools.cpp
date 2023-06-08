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
            returnKey = AddWord(s, AddWordMode::Add);
            break;
        case 'r':
            returnKey = AddWord(s, AddWordMode::Redirect);
            break;
		case 'd':
            returnKey = WordDelete(s);
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
