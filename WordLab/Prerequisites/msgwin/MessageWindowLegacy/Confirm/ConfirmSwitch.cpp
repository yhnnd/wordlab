int MessageWindow::ConfirmSwitch(int n,int x,int y,int width,int height) {
	if (n < 0) {
        n = 0;
    }

	const int blockWidth = (n > 0) ? (n == 1 ? (--width / n) : (width / n)) : 0;

    int r = (n > 0 ? 1 : 0);

	const time_t tolerance = 30000, timeA = clock();

	for (;;) {
		ListSwitchErase(x, y, n, blockWidth, height);
		ColorfulAll(r);
		ListSwitchBlock(x, y, n, r, blockWidth, height, '*');

        if (n > 5) {
            ColorfulBackground(r);
            printf("\b\b%-2d", r);
        }
#ifdef _WIN32
        // Wait keyboard hit and show time remains
        setForegroundColorAndBackgroundColor("gry-", "-blu");
		while (!kbhit()) {
			time_t time_passed = clock() - timeA;
			if (time_passed > tolerance) {
                goto end;
            }
			gotoxy(x,y+height);
			std::cout<<std::setw(2)<<std::setiosflags(std::ios::right)<<1+(tolerance-time_passed)/1000<<"s";
			Sleep(10);
		}
#endif
        ::fflush(stdin);
        std::cin.clear();
        std::cin.sync();

		const char key = getch();

        if (key == 13 || key == 10) {
            break;
        } else if(key=='0'||key==27||key==8||key==127||key=='r') {
            r = 0;
            goto end;
        } else if(key>='1'&&key<='9') {
            r = key - '0';
        } else if(key=='W'||key=='w'||key=='A'||key=='a') {
            r--;
        } else if(key=='S'||key=='s'||key=='D'||key=='d') {
            r++;
        }
		roll(r, r, (n > 0 ? 1 : 0), n);
	}
	end:
    setColor(lightwhite, "ConfirmSwitch");
	return r;
}
