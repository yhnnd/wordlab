int MessageWindow::SelectFrame(int x,int y,int width,
	const char *msg,int max,int w){
int r;
colorrecord(colorprev);
Frame(0,x,y,width,msg,0);
for(r=0;*(msg+r*w)!=0;r++){
	gotoxy(x+4,y+1+r);
	if(_background) ColorfulB(strsum(msg+r*w));
	else Colorful(strsum(msg+r*w));
	std::cout<<msg+r*w;
    }
colorreset(colorprev);
return MaxLength(msg,w);
}
