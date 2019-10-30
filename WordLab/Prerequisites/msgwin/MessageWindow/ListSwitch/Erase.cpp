void MessageWindow::ListSwitchErase(int x,int y,int n,int width,int height){
	int r;
	colorset(white);
	for(r=1;r<=n;r++) ListSwitchBlock(x,y,n,r,width,height,' ');
}
