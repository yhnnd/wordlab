int Performance(COORD pos= {6,0},int w=64,int h=11,int rift=1,int colwidth=6) {
	int lth = 0, time = clock();
	int xA = pos.X, xB = pos.X;
	int yA = pos.Y, yB = pos.Y+2+rift+h;
	chart Chart(xB+1,yB+1,w,h,colwidth,1);
	colorrecord(colorprev);
	begin:
	Dialog.output("start",lightgreen,xA,yA,0);
	Dialog.output("start",lightgreen,xB,yB,0);
	clearscreen(xB+1,yB+1,w,h);
	for( lth = 1; lth < 31; lth++ ) {
		if(libraryConsole(xA+1,yA+1,w,h,lth,time,Chart)==-1) {
			int k = MessageWindow.alert("(quit  resume  modify)",3,ScreenX/4,ScreenY/4,29,2,6);
			if(k==1) break;
			else if(k==3) {
				swap(xA,xB);
				swap(yA,yB);
				Chart.set(xB+1,yB+1,w,h,colwidth,1);
			}
			goto begin;
		}
	}
	if(lth==31) Dialog.output("completed",lightgreen,xA,yA);
	else Dialog.output("aborted",lightred,xA,yA);
	wl_getch();
	Dialog.output("reset",lightgreen,xA,yA,0);
	Dialog.output("reset",lightgreen,xB,yB,0);
	colorreset(colorprev);
}
