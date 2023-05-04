int MessageWindow::SearchCore(int showpos,int x,int y,int width,const char *msg,int max,int w,char *keyword) {
	int r, n = -1;
	colorrecord(colorprev);
    Frame(0,x,y,width,msg,max);
    gotoxy(x+4+bsvmaxlth(msg+showpos*w,"</",">/","()",",;"), y+1+showpos);
    std::cout<<" "<<keyword;
    for (r = 0; r < max; r++) {
        if (strindex(msg+r*w, keyword) != -1) {
            gotoxy(x+4, y+1+r);
            bsvlineDisableColors(msg+r*w,width,"</","/>","(",")",",;");
            n = (n > 0) ? n: r;
        }
    }
    colorreset(colorprev);
	return n;
}
