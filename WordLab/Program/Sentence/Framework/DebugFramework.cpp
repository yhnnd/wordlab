void FrameworkDebug() {
	int x = 0, y = 5;
	bool AskCharPrev = _Ask;
	bool ShowMsgPrev = _Show;
	for(;;) {
		reset_debug();
		if(DebugSettings()==false) break;
		_Ask = show_debug_message;
		_Show = show_debug_message;
		colorset(white);
		system("cls");
		banner();
		InputDebug();
		FrameworkCore(x,y);
		if(popup("Press [ENTER] to exit",-1)==KEY_ENTER) break;
	}
	_Ask = AskCharPrev;
	_Show = ShowMsgPrev;
}
