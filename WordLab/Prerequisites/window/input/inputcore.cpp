window::INPUT_STATUS window::inputcore(int& x0,int& y0,int& x,int& y){
	char * msg = text.line(y);
	char CHAR;
	bool REFRESH_PAGE = false;
	while(x>=0&&x<text.linecapacity()){
		// REFRESH PAGE
		if(x<=x0){
			x0 = x/innerWidth()*innerWidth();
			REFRESH_PAGE = true;
		}
		if(x>x0+innerWidth()){
			x0 += innerWidth();
			REFRESH_PAGE = true;
		}
		if(REFRESH_PAGE){
			Reader(WINDOW_STATUS::active,x0,y0,0);
			REFRESH_PAGE = false;
		}
		refresh(x0,y0,x,y);// REFRESH LINE
		// GET CHAR
		CHAR = getch();
	    if(CHAR==27){//ESC
	    	return INPUT_STATUS::ESCAPE;
	    }else if(CHAR==13){//NEW LINE
			return INPUT_STATUS::NEW_LINE;
		}else if(CHAR==8){//DELETE
			if(x>0){
				for(int i=--x;i<text.length(y);++i) msg[i] = msg[i+1];
				continue;
			}else return INPUT_STATUS::DELETE_LINE;
		}else if(CHAR==-32){//BIOSKEY
			CHAR = getch();
			switch(CHAR){
				case UP: return INPUT_STATUS::Up;
				case DOWN: return INPUT_STATUS::Down;
				case LEFT: return INPUT_STATUS::Left;
				case RIGHT: return INPUT_STATUS::Right;
				default: return INPUT_STATUS::UNKNOWN_BIOSKEY;
			}
		}else if(CHAR=='\t'){//TABLE
			x+=3;
			strcat(msg,"    ");
			continue;
		}
		msg[text.length(y)+1] = 0;
		for(int i=text.length(y);i>x;--i) msg[i] = msg[i-1];
		msg[x++] = CHAR;
	}
	return INPUT_STATUS::OUT_OF_LINE;
}
