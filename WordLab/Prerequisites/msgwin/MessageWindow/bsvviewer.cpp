int MessageWindow::bsvviewer(const char *route,bool _Animation,int x,int y,int w,int h,bool select) {
	int n = 0, width;
	int height = filelines(route,1);
	const int linemax = 200;
	if(h>0&&height>h) height = h;
	if(height<=0) {
		alert("<-wte>(data file lost",0,20,5,36,4,10);
		return -1;
	}

	char msgs[height][linemax];
	loadmsg((char*)msgs,route,height,linemax,1,1);
	if(height==1) {
		alert("<-wte>(no data in file",0,20,5,36,4,10);
		return 0;
	}
	strcpy(msgs[height-1],"exit");

	width=bsvmaxlths(msgs,"<",">","()",";");
	if(w>0&&width>w) width=w;

	bool background=SetBackground(true),monochrome=SetMonochrome(true);
	if(_Animation) Show(x,y,width,&msgs[0][0],height,linemax);
	else        Frame(0,x,y,width,&msgs[0][0],height,linemax);

	if(select) for(;;) {
			n=Switch(x,y,width,&msgs[0][0],height,w,n);
			if(n==-1||n==height-1) break;
		} else n=getch();

	if(_Animation) Hide(x,y,width,&msgs[0][0],height,linemax);
	else       Frame(-1,x,y,width,&msgs[0][0],height,linemax);
	SetMonochrome(monochrome);
	SetBackground(background);
	return n;
}
