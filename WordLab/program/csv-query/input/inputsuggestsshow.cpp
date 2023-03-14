int inputsuggestsshow(char *msg,char *keywords,int n,int lth,int maxresult,COORD pos) {
	int i = 0,r = 0;
	WORD color = colornow();
	colorset(backgray);
	clearscreen(pos.X-1,pos.Y+1,lth,maxresult);
	for(i=0,r=0; i<n&&r<maxresult; i++) {
		if(strindex(keywords+i*lth,msg)>=0) {
			colorset(backlight|backyellow);
			clearline(pos.X-1,pos.Y+1+r,lth);
			cout<<keywords+i*lth;
			r++;
		}
	}
	colorreset(color);
}
