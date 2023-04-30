void clearscreen(const int x,const int y,const int width,const int height,const char fill){
	for(int r = 0; r < height; r++) {
	    gotoxy(x, y + r);
	    std::cout<<std::setw(width)<<std::setfill(fill)<<"";
	}
}
