int WLTools(string s) {
    popup("#setMode('y++');");
    popup("#enableBorderTop=true;");
    popup("#offsetY=0;");
	popup("press [A] to add <fore yellow>(",s,")",0);
	popup("press [D] to delete <fore red>(",s,")",0);
	popup("press [U] to update <fore cyan>(",s,")",0);
    popup("#setMode('y=1');");
	switch (getch()) {
		case 'a': AddWord(s); break;
		case 'd': WordDelete(s); break;
		case 'u': WordUpdate(s); break;
		default:
            errorlog("WLTools(s)", "option error");
            return 0;
	}
	return 1;
}
