int multitask(int x,int y,int width,char Menu[][LINEMAX],int T=0,int n=0,bool backcolor=0){
	int a=-1;
	bool backcolorold=MessageWindow.SetBackground(backcolor);
	if(version==OLD){
	    if(T==0) MessageWindow.Show(x,y,width,&Menu[0][0],0,LINEMAX);
		else MessageWindow.Frame(0,x,y,width,&Menu[0][0],0);
		a =  MessageWindow.Switch (x,y,width,&Menu[0][0],0,LINEMAX,n);
	}
	else if(version==NEW)a = MessageBlock.Switcher(Menu);
	MessageWindow.SetBackground(backcolorold);
	return a;
}
