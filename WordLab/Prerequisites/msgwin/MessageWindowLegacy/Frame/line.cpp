void MessageWindow::LineColorful(int n) {
    if (_background) {
        ColorfulB((_Monochrome||!_AutoColorful)?0:n);
    } else {
        Colorful ((_Monochrome||!_AutoColorful)?0:n);
    }
}

int MessageWindow::Line(int x,int y,int width,const char *what,int n){
	gotoxy(x,y++);
	colorset(bothlightblue);
	std::cout<<"*";
	colorset(backdarkwhite);
	std::cout<<"   ";
	LineColorful(n);
	bsvline(what, width, "<", ">", "(", ")", ",;");
	colorset(bothlightblue);
	std::cout<<"*";
	return y;
}

int MessageWindow::line(int x,int y,int width) {
	int r;
	gotoxy(x,y++);
	colorset(bothlightblue);
	std::cout<<"*";
	colorset(backdarkwhite);
	std::cout<<"   ";
	for(r=0;r<=width;r++) std::cout<<" ";
	colorset(bothlightblue);
	std::cout<<"*";
	return y;
}
