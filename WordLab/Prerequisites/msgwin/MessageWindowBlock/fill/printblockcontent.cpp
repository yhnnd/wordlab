void messageblock::printBlockContent(const int x, const int y, const int width, const std::string msg) {
	if( x<0 or y<0 ) {
        return;
    }
	gotoxy(x,y);
    setForegroundColorAndBackgroundColor("#wte-", "-blk");
	std::string msgname = msg.find(',') != std::string::npos ? msg.substr(0,msg.find(',')) : msg;
	std::cout << std::setfill(' ') << std::setw(width) << std::left << std::setiosflags(std::ios::left) << msgname;
}
