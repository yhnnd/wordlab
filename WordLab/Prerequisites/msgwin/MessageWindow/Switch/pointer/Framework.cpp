int MessageWindow::Pointer(const int x, const int y, const int max, const int n, const int nprev, const bool flag0 = true, const bool flag1 = true) {
	colorrecord(colorprev);
	if (nprev>=0&&nprev<max) {
        colorset(bothdarkwhite);
        gotoxy(x,y+nprev);
#ifdef __APPLE__
        movexy(1, 0);
#endif
        std::cout<<"   ";
    }
	if (flag1==true) {
        colorset(bothlightgreen);
        gotoxy(x,y+max-2);
#ifdef __APPLE__
        movexy(1, 0);
#endif
        std::cout<<"-1 ";
    }
	if (flag0==true) {
        colorset(bothlightred);
        gotoxy(x,y+max-1);
#ifdef __APPLE__
        movexy(1, 0);
#endif
        std::cout<<" 0 ";
    }
	if (n>=0&&n<max) {
        colorset(bothlightyellow);
        gotoxy(x,y+n);
#ifdef __APPLE__
        movexy(1, 0);
#endif
        std::cout<<"-->";
    }
	colorreset(colorprev);
	return getch();
}
