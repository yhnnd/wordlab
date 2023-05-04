void MsgWinSwiShowChoosed(int radius,int x,int y,int width,int n,const char *what,int max,int w){
	for(int r=-radius;r<=radius;r++){
	    MsgWinSwiShwChsCore(r,x,y+r,width,what+((n+r+max)%max)*w);
	}
}
