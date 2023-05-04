int MessageWindow::Edge(int x,int y,int width){
	int r;
	colorrecord(colorprev);
	colorset(bothlightblue);
	gotoxy(x,y++);
	for(r=0;r<=width+5;r++) std::cout<<((r%2==0)?"*":" ");
	colorreset(colorprev);
	return y;
}
