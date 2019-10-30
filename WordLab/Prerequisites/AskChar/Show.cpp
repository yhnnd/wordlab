void AskCharShow(std::string cache[]){
	int r,rl;
    recordxy(pos);
    colorrecord(colorprev);
	if(_ReverseColor) colorset(backgray);
	else colorset(gray);
	for(r=0;r<_CacheMax;r++){
		if(r==_CacheMax-1){
		    if(_ReverseColor) colorset(backwhite);
			else colorset(white);
			}
		clearline(0,ScreenY-_CacheMax+r);
		for(rl=0;
		cache[r][rl]!='\0'&&
		cache[r][rl]!='\n'&&
		cache[r][rl]!=';'&&
		rl<ScreenX;
		rl++) std::cout<<cache[r][rl];
		}
	colorreset(colorprev);
	resetxy(pos);
}
