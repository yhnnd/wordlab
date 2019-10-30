void fatalerror(int delayperiod){
	int r,w=30,x=(ScreenX-w)/2,y=6,max=10;
	progressbar bar(max,true,false);
	for(;;){
	    for(r=0;r<max;r++) if(bar.show(x,y+r,r,0,w,allred,bothlightred)==-1) return;
	    for(r=0;r<max;r++) if(bar.show(x,y+r,r,rand()%(w+1),w,allred,bothlightred)==-1) return;
		if(wait(delayperiod,10,1,0,0)) return;
	}
}
