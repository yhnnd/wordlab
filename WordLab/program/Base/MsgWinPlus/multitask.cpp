int multitask(int x,int y,int width,char Menu[][LINEMAX],int T=0,int n=0,bool backcolor=0){
	int a = -1;
	bool backcolorold = MessageWindow.SetBackground(backcolor);
#if defined(_WIN32)
	if (version==OLD) {
	    if (T==0) {
            MessageWindow.Show(x,y,width,&Menu[0][0],0,LINEMAX);
        } else {
            MessageWindow.Frame(0,x,y,width,&Menu[0][0],0);
        }
		a =  MessageWindow.Switch (x,y,width,&Menu[0][0],0,LINEMAX,n);
	} else if(version==NEW) {
        a = MessageBlock.Switcher(Menu);
    }
#elif defined(__APPLE__)
    const int maxlength = MaxLength(&Menu[0][0],LINEMAX);
    if (version==OLD) {
        if (T==0) {
            MessageWindow.Show(x,y,width,&Menu[0][0],0,LINEMAX);
        } else {
            MessageWindow.Frame(0,x,y,width,&Menu[0][0],0);
        }
        a =  MessageWindow.Switch (x,y,width,&Menu[0][0],0,LINEMAX,n);
    } else if(version==NEW) {
        a = MessageBlock.Switcher(Menu);
    }

    if (a >= 0 && a < maxlength) {
//        popup("<grn->(your choice:) ", tostring(a), -1);
    } else {
        popup("<red-> (error) <ylw->(\\(illegal choice\\))",-1);
    }
#endif
	MessageWindow.SetBackground(backcolorold);
	return a;
}
