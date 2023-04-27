void messageblock::adjustshowall(int r){
	colorrecord(colorprev);
	for(int n=1;n<=7;n++){
		gotoxy(x+1,y+1+n);
	    if(n==r){
			colorset(bothlightyellow);
			std::cout<<"-->";
			colorset(backlightyellow);
		}else{
			colorset(backdarkwhite);
			std::cout<<"   ";
		}
		for(int r=0;r<=aww;r++) std::cout<<" ";
		gotoxy(x+4,y+1+n);
		adjusttitle(n,1);
    }
    colorset(colorprev);
}
