char fatalerror(int delayperiod) {
	int r,w=30,x=(ScreenX-w)/2,y=6,max=10;
	progressbar bar(max,true,false);
	for (;;) {
	    for(r=0;r<max;r++) {
            if(bar.show(x,y+r,r,0,w,bothred,bothlightred)==-1) {
                return 0;
            }
        }
	    for(r=0;r<max;r++) {
            if(bar.show(x,y+r,r,rand()%(w+1),w,bothred,bothlightred)==-1) {
                return 0;
            }
        }
        char ch;
#ifdef _WIN32
        ch = wait(delayperiod,10,1,0,0);
#elifdef __APPLE__
        ch = getch();
#endif
		if (ch) {
            return ch;
        }
	}
}
