void Framework() {
	int x = 0, y = 5;
	bool Askprev = _Ask;
	_Ask = false;
	for(;;) {
		reset();
		colorset(white);
		system("cls");
		banner();
		for(rwin = 0;; rwin++) {
			punct = Input(x,y);
			if(punct==0) break;
			else if(punct==13) break;
			FrameworkCore(x,y);
		}
		if(punct==0) break;
		if(popup("Press [ENTER] to exit",-1)==13) break;
	}
	_Ask = Askprev;
}
