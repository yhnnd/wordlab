int MessageWindow::ListSwitch(int rprev,int N,int x,int y,int width){
	int  rY,rX,r=rprev;
	char key;
	ListSwitchErase(x,y,N,width/N,1);
	ColorfulAll(r);
	ListSwitchBlock(x,y,N,r,width/N,1,'*');
	colorset(white);
	key = wl_getch();
	     if(key==13) return r;
	else if(key=='0'||key=='r'||key==27||key==8) return -1;
	else if(key=='A'||key=='a'||key=='W'||key=='w') r--;
	else if(key=='D'||key=='d'||key=='S'||key=='s') r++;
	return r;
}
