void window::ScrollBar(WINDOW_STATUS CurrentStatus,int y0){
	if(CurrentStatus != WINDOW_STATUS::active) return;
	//SET SCROLLBAR WIDTH = PADDING RIGHT
	int ScrollBarWidth = padding.right;
	//SET SCROLLBAR LENGTH
	int ScrollBarLength = innerHeight() < text.size() ? (innerHeight() * innerHeight() / text.size()) : innerHeight();
	if( ScrollBarWidth <= 0 || ScrollBarLength <= 0 || ScrollBarLength >= innerHeight() ) return;
	//SET PADDING RIGHT COLOR
    setColorByCommand(color[WINDOW_STATUS::active].padding.background, "ScrollBar");
	//CLEAR PADDING RIGHT
	for(int y = 0; y < innerHeight(); ++y){
		gotoxy(width - innerRight(),innerTop() + y);
		std::cout<<std::setw(ScrollBarWidth)<<"";
	}
	//SET SCROLLBAR COLOR
    setColorByCommand(color[WINDOW_STATUS::inactive].padding.background, "ScrollBar");
	//SET SCROLLBAR POSITION
	int ScrollBarY = y0 * innerHeight() / text.size();
	//PRINT SCROLLBAR
	for(int y = 0; y < ScrollBarLength; ++y){
		gotoxy(width - innerRight(),innerTop() + ScrollBarY + y);
		std::cout<<std::setw(ScrollBarWidth)<<"";
	}
}
