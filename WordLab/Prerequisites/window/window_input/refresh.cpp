void window::refresh(int x0,int y0,int x,int y){
	auto line = text.line(y);
	// SET LINE POSITION
	gotoxy(innerLeft(),innerTop()+(y-y0));
	// SET LINE COLOR
	if(text.iscmd&&text.iscmd[y]){
        setColorByCommand(color[WINDOW_STATUS::active].error.content, "refresh");// cmd
	} else {
        setColorByCommand(color[WINDOW_STATUS::active].text[y % 2].content, "refresh");// text
	}
	// PRINT LINE
	for(int i=0;i<innerWidth();++i){
		if(x0+i<text.length(y))	std::cout<<line[x0+i];
		else break;
	}
	// SET BACKGROUND COLOR
	if(text.iscmd and text.iscmd[y]){
        setColorByCommand(color[WINDOW_STATUS::active].error.background, "refresh");// error
	} else {
        setColorByCommand(color[WINDOW_STATUS::active].text[y % 2].background, "refresh");// text
	}
	// PRINT BACKGROUND
	std::cout<<std::setw(innerWidth()-(text.length(y)-x0))<<"";
	// RESET CURSOR
	gotoxy(innerLeft()+(x-x0),innerTop()+(y-y0));
}
