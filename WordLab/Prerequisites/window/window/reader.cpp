int window::Reader(WINDOW_STATUS CurrentStatus,int x0,int y0,bool INIT) {
	applysettings();
	if(INIT) {
		colorsetcmd(color[CurrentStatus].padding.background);
		clearscreen(outerLeft(),outerTop(),outerWidth(),outerHeight());
	}
	gotoxy(outerLeft()+(outerWidth()-title.length())/2,outerTop());
	colorsetcmd(color[CurrentStatus].padding.content);
	std::cout<<title;
	for(int y=y0; y<y0+innerHeight(); ++y) {
		//clear line
		if(text.iscmd[y]) colorsetcmd(color[CurrentStatus].error.background);//error
		else colorsetcmd(color[CurrentStatus].text[y%2].background);
		clearline(innerLeft(),innerTop()+(y-y0),innerWidth());
		//print text
		if(y<text.capacity()) {
			if(text.iscmd[y]) colorsetcmd(color[CurrentStatus].error.content);//error
			else colorsetcmd(color[CurrentStatus].text[y%2].content);
			for(uint x=x0; x<text.linecapacity()&&(x-x0)<innerWidth(); ++x) {
				if (text.line(y)[x]==0||text.line(y)[x]==EOF) {
                    break;
                }
				std::cout<<text.line(y)[x];
			}
		}
	}
	ScrollBar(CurrentStatus,y0);
	colorsetcmd("wte-");
	return text.size();
}
