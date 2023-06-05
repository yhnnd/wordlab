int window::Reader(WINDOW_STATUS CurrentStatus,int x0,int y0,bool INIT) {
	applysettings();
	if(INIT) {
        setColorByCommand(color[CurrentStatus].padding.background, "Reader");
		clearScreen(outerLeft(),outerTop(),outerWidth(),outerHeight());
	}
	gotoxy(outerLeft()+(outerWidth()-title.length())/2,outerTop());
    setColorByCommand(color[CurrentStatus].padding.content, "Reader");
	std::cout<<title;
	for(int y=y0; y<y0+innerHeight(); ++y) {
		//clear line
		if(text.iscmd[y]) {
            setColorByCommand(color[CurrentStatus].error.background, "Reader");//error
        } else {
            setColorByCommand(color[CurrentStatus].text[y % 2].background, "Reader");
        }
		clearline(innerLeft(),innerTop()+(y-y0),innerWidth());
		// print text
		if (y<text.capacity()) {
			if (text.iscmd[y]) {
                setColorByCommand(color[CurrentStatus].error.content, "Reader");//error
            } else {
                setColorByCommand(color[CurrentStatus].text[y % 2].content, "Reader");
            }
			for (uint x=x0; x<text.linecapacity()&&(x-x0)<innerWidth(); ++x) {
				if (text.line(y)[x]==0||text.line(y)[x]==EOF) {
                    break;
                }
				std::cout<<text.line(y)[x];
			}
		}
	}
	ScrollBar(CurrentStatus,y0);
    setColorByCommand("wte-", "Reader");
	return text.size();
}
