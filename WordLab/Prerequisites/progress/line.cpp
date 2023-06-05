void progressbar::line(int x,int y,int nprev,int n,char s,WORD color){
	int r = nprev;
	gotoxy(x + r, y);
	recordColor(colorprev, "progressbar::line");
    setColor(color, "progressbar::line");
	for (; r < n; r++) {
        std::cout<<s;
    }
    resetColor(colorprev, "progressbar::line");
}
