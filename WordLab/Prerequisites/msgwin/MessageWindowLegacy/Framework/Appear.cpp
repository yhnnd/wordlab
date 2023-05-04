void MessageWindow::Show(int x,int y,int width,const char *msg,int h,int w) {
	int d,begin,max=MaxLength(msg,w);
	d=(max>8)?2:1;
	for(begin=max; begin>=0; begin-=d) Frame(begin,x,y,width,msg,h,w);
	if(d==2&&max%2) Frame(0,x,y,width,msg,h,w);
}

void MessageWindow::Show(int x,int y,int width,int max,int h) {
	int begin,d=(max>8)?2:1;
	for(begin=max; begin>=0; begin-=d) Frame(begin,x,y,width,max,h);
	if(d==2&&max%2) Frame(0,x,y,width,max,h);
}
