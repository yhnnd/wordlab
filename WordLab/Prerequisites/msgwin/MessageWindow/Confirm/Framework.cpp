int MessageWindow::Confirm(int n,int x,int y,int width,const char *what,int max,int w){
    int r=0;
    max=MaxLength(what,max,w);
    recordxy(xy);
	bool background = SetBackground(1),monochrome = SetMonochrome(1);
    Frame(0,x,y,width,what,max,w);
    r = ConfirmSwitch(n,x+1,y+max-1,width+5,2);
    Frame(-1,x,y,width,max,max);
	SetMonochrome(monochrome);
	SetBackground(background);
    resetxy(xy);
    return r;
}
