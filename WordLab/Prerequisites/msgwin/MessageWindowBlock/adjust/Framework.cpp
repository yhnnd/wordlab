void messageblock::Adjust() {
	int r = 1, T = 0, key;
	recordColor(colorprev, "Adjust");
	for (;;T = true) {
	    if (T == 0) {
            Show(x,y,aww,awh,awh);
        } else {
            Frame(0,x,y,aww,awh,awh);
        }
		gotoxy(x+1,y+1);
        setColor(backdarkwhite, "Adjust");
		std::cout<<"Message window Settings";
		for(;;){
			adjustShowAll(r);
			if((key=getch()) == 13 || key == 10) {
                break;
            } else if (key==8 || key==27 || key==127) {
                goto end;
            } else if(key=='a'||key=='w') {
                r--;
            } else {
                r++;
            }
			if(_LoopLock) {
                roll(r,r,1,7);
            } else {
                limit(r,r,1,7);
            }
		}
		if (r == 7) {
            if (Report(x,y,aww,awh,ReportFileRoute)) {
                break;
            }
        } else {
		    gotoxy(x+4,y+1+r);
			adjusttitle(r,0);
			if (adjustset(r)) {
                break;
            }
		}
	}
	end:
	defaultssave();
	Erase(x,y,aww,awh);
    resetColor(colorprev, "Adjust");
}
