void dialog::settings(int x,int y) {
	int buttonMax = 3;
	int buttonHeight[buttonMax] = {4,3,4};
	WORD buttonColor[buttonMax] = {bothgreen,bothyellow,bothred};
	WORD buttonActiveColor[buttonMax] = {bothlightgreen,bothlightyellow,bothlightred};
	int buttonSelected = 0;
	int beginX = x + 1;
	std::vector<std::string> optionsName = {"clear output","resume","clear input"};
	this->output("title: dialog settings");
	for(;;) {
		gotoxy(beginX,y);
		for(int n = 0; n < buttonMax; ++n ) {
			colorset( n == buttonSelected ? buttonActiveColor[n] : buttonColor[n] );
			for(int i = 0; i < buttonHeight[n]; ++i) {
				gotoxy(beginX,getxy().Y+1);
				std::cout<<(n==buttonSelected?"***":"   ");
			}
		}
		auto key = getch();
		if ( key == 'w' ) {
			--buttonSelected;
		} else if ( key == 's') {
			++buttonSelected;
		} else if ( key == KEY_ESC || key == KEY_DELETE ) {
		EXIT:
			this->output("start");
			this->output("");
			break;
		} else if ( key == KEY_ENTER ) {
			if ( buttonSelected == 0 ) {
				_for(e,memoryout) *e = "";
			} else if ( buttonSelected == 1 ) {
				goto EXIT;
			} else if ( buttonSelected == 2 ) {
				_for(e,memoryin) *e = "";
			}
			this->output("start");
			this->output("");
		}
		limit( buttonSelected, buttonSelected, 0, buttonMax-1 );
		this->output("title: "+optionsName[buttonSelected]);
	}
}
