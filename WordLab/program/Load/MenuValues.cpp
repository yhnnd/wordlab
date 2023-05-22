void load::Values() {
	const int x = 0, y = 9, width = 36;
	const int total = filelines(SetValuesRoute"en.csv",true) - 2;
	if (total <= 0) {
        popup("<Critical Error> SetValues menu file lost",-1);
        return;
    }
	char Menu[total+2][LINEMAX];
	if(!loadmsg((char*)Menu,SetValuesRoute"en.csv",total+2,LINEMAX,1,1)){
		popup("<Critical Error> SetValues cannot load menu",-1);
		return;
	}
	bool background = MessageWindow.SetBackground(true);

	MessageWindow.Frame(0,x,y,width,&Menu[0][0],total + 2);

    int r = 0, rprev = 0;
	for (;;) {
	    togglesShow(x, y, width, _Show, total,
            _Show,
            _Ask,
            _AskOnce,
            _AutoOnce,
            _ReverseColor,
			MessageWindow._background,
            MessageWindow._Monochrome,
            MessageWindow._LoopLock,
			VL,
            SayStyle
        );
	    r = MessageWindow.Switch(x,y,width,&Menu[0][0],total+2,LINEMAX,rprev);
		toggles(x, y, width, _Show, r, total,
            &_Show,
            &_Ask,
            &_AskOnce,
            &_AutoOnce,
            &_ReverseColor,
			&MessageWindow._background,
            &MessageWindow._Monochrome,
            &MessageWindow._LoopLock,
			&VL,
            &SayStyle
        );
		if (r <= 0 || r > total) {
            break;
        }
        rprev = r;
        load::systemDefaults(SystemDefaultsRoute, load::mode::saveDefaults);
	}
	MessageWindow.SetBackground(background);
}
