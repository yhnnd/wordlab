int confirmationbar(int x,int y,int width,int delay){
	int i=0;
	progressbar bar(1,1,1);
	for(i=0;i<=width;i++){
		if(bar.show(x,y,0,i,width)==-1) break;
		if(delay>0&&wait(delay,1,0)&&MessageWindow.alert("cancel?",2,ScreenX/4,ScreenY/4,20,2,6)==1) break;
		}
	return (i>width)?0:-1;
	}
