int MessageWindow::Search(int showpos,int x,int y,int width,const char *msg,int max,int w){
	char keyword[w], c;
	int r, n= -1;
	strclr(keyword);
	for(r=0;(c=getch())!=13;){
	    if(c==8){
			keyword[r]=0;
			keyword[--r]=0;
		} else {
			keyword[r++]=c;
			keyword[r+1]=0;
		}
		if(r<0) return -2;
	    n = SearchCore(showpos,x,y,width,msg,max,w,keyword);
	}
	return n;
}
