void MessageWindow::Hide(int x,int y,int width,const char *msg,int h,int w) {
	int r,d,begin,max=MaxLength(msg,w);
	d=(max>8)?2:1;
	for(begin=0; begin<=max; begin+=d) {
		Frame(begin,x,y,width,msg,h);
		if(begin) {
			for(r=0; r<=d; r++) {
				clearline(x,y+max-begin+r+1,width+6);
			}
		}
	}
	for(r=0; r<=d; r++) {
		clearline(x,y+r,width+6);
	}
}

void MessageWindow::Hide(int x,int y,int width,int max,int h) {
	int r,d=(max>8)?2:1,begin;
	for(begin=0; begin<=max; begin+=d) {
		Frame(begin,x,y,width,max,h);
		if(begin) {
			for(r=0; r<=d; r++) {
				clearline(x,y+max-begin+r+1,width+6);
			}
		}
	}
	for(r=0; r<=d; r++) {
		clearline(x,y+r,width+6);
	}
}
