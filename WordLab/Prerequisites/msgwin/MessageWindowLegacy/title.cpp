void MessageWindow::Title(int x,int y,int w,const std::string msg){
	gotoxy(x, y);
    setForegroundColorAndBackgroundColor("wte-", "-blu");
	std::cout<<std::setiosflags(std::ios::left)<<std::setw(w) << msg;
	// cout setw(w) so as to clear previous title
}
