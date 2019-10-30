void MsgWinSwiShwChsCore(int radius,int x,int y,int width,const char *what){
	int r;
	colorrecord(colorprev);
	colorset((radius)?white:white|backlightblue);
	clearline(x,y,width);
	switch(abs(radius)){
	    case  0: colorset(white|backlightblue);break;
	    case  1: colorset(gray);break;
	    case  2: colorset(blue);break;
	    default: colorset(lightred);break;
	}
	for(r=0;r<=width&&what[r]!=','&&what[r]!=';'&&what[r]!='\0';r++){
		std::cout<<what[r];
	}
	colorreset(colorprev);
}
