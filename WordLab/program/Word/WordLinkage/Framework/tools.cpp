char WLTools(string s) {
    popup("#setMode('y++');");
    popup("#enableBorderTop=true;");
    popup("#offsetY=0;");
	popup("press [A] to add <fore yellow>(",s,")",0);
	popup("press [D] to delete <fore red>(",s,")",0);
	popup("press [U] to update <fore cyan>(",s,")",0);
    popup(set_mode_y_is_constant);

    const char choice = ::tolower(getch());
    char returnKey = 0;

	switch (choice) {
		case 'a':
            returnKey = AddWord(s);
            break;
		case 'd':
            returnKey = WordDelete(s);
            break;
		case 'u':
            returnKey = WordUpdate(s);
            break;
		default:
            errorlog("WLTools(s)", "option error");
            returnKey = 0;
            break;
	}
	return returnKey;
}
