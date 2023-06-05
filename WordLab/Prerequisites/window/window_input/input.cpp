window::INPUT_STATUS window::input(int& x0,int& y0,int& x,int& y){
	auto line = text.line(y);
	if(line==nullptr) {
        return INPUT_STATUS::OUT_OF_PAGE;
    }
	INPUT_STATUS STATUS = this->inputcore(x0,y0,x,y);
	if (y+1>text.size()) {
        text.setsize(y+1);
    }
    setColor(lightwhite, "window::input");
	return STATUS;
}
