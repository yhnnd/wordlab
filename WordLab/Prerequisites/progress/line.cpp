void progressbar::line(int x,int y,int nprev,int n,char s,WORD color){
	int r = nprev;
	gotoxy(x + r, y);
	colorrecord(colorprev);
	colorset(color);
	for (; r < n; r++) {
        std::cout<<s;
    }
	colorreset(colorprev);
}
