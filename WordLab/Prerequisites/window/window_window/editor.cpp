int window::Editor(int x0,int y0,int x,int y) {
	int key = 0;
	Reader(WINDOW_STATUS::active,x0,y0,1);
	for(; key != -2 && y >= 0 && y < text.capacity(); y += (key*2)+1 ) {
		x = strlen(text.line(y));
INPUT:
		int x0prev = x0,y0prev = y0;
		if( y0 > y ) y0 = y;//first line > focused line
		if( y0 <= y-innerHeight() ) y0 = y-innerHeight()+1;//first line <= focused line - height
		if( x0 > x ) x0 = x;//first char > focused char
		if( x0 <= x-innerWidth() ) x0 = x-innerWidth()+1;//first char <= focused char - width
		if( x0 < 0 || x < innerWidth() ) x0 = 0;//optimize first char
		if( y0 < 0 ) y0 = 0;
		if( x0 != x0prev || y0 != y0prev ) Reader(WINDOW_STATUS::active,x0,y0,0);
		//status bar
        setColorByCommand(color[WINDOW_STATUS::active].padding.content, "Editor");
		gotoxy(innerLeft(),outerTop()+innerHeight()+1);
		if(innerWidth()>40) std::cout<<" PageSize="<<text.capacity();
		if(innerWidth()>50) std::cout<<" TotalLine="<<text.size();
		if(innerWidth()>40) std::cout<<" LineSize="<<text.linecapacity();
		std::cout<<" Line="<<y<<" Col="<<x<<"  ";
		//edit text.line(n)
		key = input(x0,y0,x,y);
		applysettings();
		if(strcmp(text.line(y),"#settings();") == 0) {
			strclr(text.line(y));
			std::cout<<"w="<<this->width
			         <<" h="<<this->height
			         <<" l="<<this->margin.left
			         <<" r="<<this->margin.right
			         <<" t="<<this->margin.top
			         <<" b="<<this->margin.bottom
			         <<" pl="<<this->padding.left
			         <<" pr="<<this->padding.right;
		} else if(strcmp(text.line(y),"#set();") == 0) {
			strclr(text.line(y));
			auto setparam = [](const char * name,int & value)->void{
				char msg[16];
				std::cout<<" "<<name<<"=";
				listen(msg,0,1,{13},16);
				if(isdigit(msg[0])) {
                    value = toInt(msg);
                } else {
                    std::cout<<value;
                }
			};
			setparam("w",this->width);
			setparam("h",this->height);
			setparam("l",this->margin.left);
			setparam("r",this->margin.right);
			setparam("t",this->margin.top);
			setparam("b",this->margin.bottom);
			setparam("pl",this->padding.left);
			setparam("pr",this->padding.right);
		}
		if(key == UP) { //cursor up
			if(--y<0) y = 0;//MINIMUM bound
			int lth = strlen(text.line(y));
			if(lth<x) x = lth;
			goto INPUT;
		} else if(key == DOWN) { //cursor down
			if(++y >= text.size()) y = text.size()-1;//MAXIMUM bound
			auto lth = strlen(text.line(y));
			if(lth<x) x = lth;
			goto INPUT;
		} else if(key == LEFT) { //cursor left
			if(--x<0) {
				if(--y >= 0) x = strlen(text.line(y));
				else {
					y = 0;
					x = 0;
				}
			}
			goto INPUT;
		} else if(key == RIGHT) { //cursor right
			if(++x > strlen(text.line(y))) {
				if(++y < text.size()) x = 0;
				else {
					y = text.size()-1;
					--x;
				}
			}
			goto INPUT;
		}
	}
    setColorByCommand("wte-", "Editor");
	return text.size();
}
