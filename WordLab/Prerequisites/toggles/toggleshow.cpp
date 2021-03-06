void toggleShow(int x,int y,bool lock,bool delay,bool showdigit){
	recordxy(pos);
	colorrecord(colorprev);
	int r=(delay)?0:3;
	
	for(;r<=3;r++){
		gotoxy(x,y);
		colorset(backlight|backgreen);
		std::cout<<"   ";
		
		gotoxy(x+3,y);
		colorset(backlight|backred);
		std::cout<<"   ";
		
	    if(lock) gotoxy(x+r,y);
		else gotoxy(x+3-r,y);
		
		if(showdigit) colorset(backwhite);
		else colorset(bothwhite);
		
		std::cout<<"   ";
	}
	std::cout<<"\b\b"<<lock;
	colorreset(colorprev);
	resetxy(pos);
}
