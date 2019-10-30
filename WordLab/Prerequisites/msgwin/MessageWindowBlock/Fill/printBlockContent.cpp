void messageblock::printBlockContent(int x,int y,int width,std::string msg) {
	if( x<0 or y<0 ) return;
	gotoxy(x,y);
	colorset(light);
	std::string msgname = msg.find(',')!=std::string::npos ? msg.substr(0,msg.find(',')) : msg;
	std::cout<<std::setw(width)<<std::setiosflags(std::ios::left)<<msgname;
}
