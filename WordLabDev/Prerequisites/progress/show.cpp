int progressbar::show(int x,int y,int thread,int n,int width,WORD back,WORD fore){
	if(n>0&&nprev[thread]==n) return 0;
	else if(n==0) line(x,y,0,width,'-',back);
    else  line(x,y,nprev[thread],n,'*',fore);
    nprev[thread]=n;
    if(_AllowInterrupt){
	    if(kbhit()){
		    key=getch();
			if(_AskBeforeQuit){
			    if(MessageWindow.alert("cancel?",2,ScreenX/4,ScreenY/4,20,2,6)==1) return -1;
				}
			else return -1;
			}
		}
    return 0;
    }
