int MessageWindow::Switch(int x,int y,int width,char *what,int max,int w,int n) {
	char r, nprev = -1;
	if(max<=0) max = MaxLength(what,w);
	for(;;) {
	begin:
		limit(n,n,0,max-1);
		r = Pointer(x+1,y+1,max,n,nprev);
		nprev = n;
		if(r==13)  break;
		else if(r=='r'||r=='R'||r==8||r==27) return -1;
		else if(r=='l'||r=='L') {
			deny(_LoopLock,_LoopLock);
		} else if(r=='i'||r=='I') {
			Change(x,y,width,what,max,w);
		} else if(r=='n'||r=='N') {
			bsvviewer("buf.bsv");
			Frame(0,x,y,width,what,max);
		} else if(r=='e'||r=='E'||r=='w'||r=='W') n--;
		else if(n<max-1||_LoopLock) n++;
		if(_LoopLock) SwitchLoop(x,y,width,what,max,w,&n);
	}
	if(!_background) Highlight(what+n*w);
	if(n==0) if((n=Search(0,x,y,width,what,max,w))==-2) goto begin;
	return n;
}

int MessageWindow::Switch(int x,int y,int width,std::vector<std::string> what,int n) {
	char c, nprev=-1;
	int max = what.size();
	for(;;) {
		limit(n,n,0,max-1);
		c = Pointer(x+1,y+1,max,n,nprev);
		nprev = n;
		if(c==13)  break;
		else if(c=='r'||c=='R'||c==8||c==27) return -1;
		else if(c=='e'||c=='E'||c=='w'||c=='W') n--;
		else if(n<max-1||_LoopLock) n++;
		if(_LoopLock) roll(n,n,0,max-1);
	}
	if(!_background) Highlight(what[n].c_str());
	return n;
}
