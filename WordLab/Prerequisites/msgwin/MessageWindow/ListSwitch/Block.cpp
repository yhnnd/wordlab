void MessageWindow::ListSwitchBlock(int x,int y,int n,int r,int width,int height,char c){
	if(n<=0||r<=0) return;
	int rx,ry;
	if(width<2) width=2;
	if(height<1) width=1;
	for(ry=0;ry<height;ry++){
	    for(rx=0;rx<width;rx++){
	        gotoxy(x+rx+(r-1)*width,y+ry);
	        std::cout<<c;
	    }
	}
}
