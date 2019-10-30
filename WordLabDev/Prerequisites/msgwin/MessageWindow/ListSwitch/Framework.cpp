int MessageWindow::ListSwitch(int N,int x,int y,int width){
	int r,rY,rX;
	char key;
	for(r=1;;){
		ListSwitchErase(x,y,N,width/N,1);
		ColorfulAll(r);
		ListSwitchBlock(x,y,N,r,width/N,1,'*');
		colorset(white);
		key = getch();
		     if(key==13)  break;
		else if(key=='0'||key=='r'||key==27||key==8) return 0;
		else if(key=='A'||key=='a'||key=='W'||key=='w') r--;
		else r++;
		limit(r,r,1,N);
	}
	return r;
}
