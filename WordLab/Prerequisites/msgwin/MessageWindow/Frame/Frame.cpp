// message type: C const char *
void MessageWindow::Frame(int begin,int x,int y,int width,const char *what,int h,int w) {
	colorrecord(colorprev);
	int n,max = MaxLength(what,w);
	if(h==0) h = max;
	if(begin==-1) {
		Erase(x,y,width,max);
		colorreset(colorprev);
		return;
	}
	if(begin==0) y = Edge(x,y,width);
	for(n=begin; n<max&&n<h; n++) y = Line(x,y,width,what+n*w,n);
	Edge(x,y,width);
	colorreset(colorprev);
}
// message type: C++ vector<string>
void MessageWindow::Frame(int begin,int x,int y,int width,std::vector<std::string> msgs) {
	colorrecord(colorprev);
	int max = msgs.size();
	if(begin==-1) {
		Erase(x,y,width,max);
	} else {
		if(begin==0) y = Edge(x,y,width);
		for( int n = begin; n < max; n++ ) {
			y = Line(x,y,width,msgs[n].c_str(),n);
		}
		Edge(x,y,width);
	}
	colorreset(colorprev);
}
// no message
void MessageWindow::Frame(int begin,int x,int y,int width,int max,int h) {
	int n;
	colorrecord(colorprev);
	if(h==0) h = max;
	if(begin==-1) {
		Erase(x,y,width,max);
		colorreset(colorprev);
		return;
	}
	if(begin==0) y = Edge(x,y,width);
	for(n=begin; n<max&&n<h; n++) y = line(x,y,width);
	Edge(x,y,width);
	colorreset(colorprev);
}
