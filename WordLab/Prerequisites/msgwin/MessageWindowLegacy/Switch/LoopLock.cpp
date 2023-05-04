void MessageWindow::SwitchLoop(int x,int y,int width,const char *what,int max,int w,int *n) {
	roll(*n,*n,0,max-1);
	if(_background) MsgWinSwiShowChoosed(0,x+4      ,y+max+1,width,*n,what,max,w);
	else if(max<=8) MsgWinSwiShowChoosed(1,x+width+6,y+max+1,width,*n,what,max,w);
	else            MsgWinSwiShowChoosed(2,x+width+6,y+max+1,width,*n,what,max,w);
}
