void messageblock::adjustShowAll(int r){

	recordColor(colorprev, "adjustShowAll");

	for(int n=1;n<=7;n++){
		gotoxy(x+1,y+1+n);
	    if (n==r) {
            setColor(bothlightyellow, "adjustShowAll");
			std::cout<<"-->";
            setColor(backlightyellow, "adjustShowAll");
		} else {
            setColor(backdarkwhite, "adjustShowAll");
			std::cout<<"   ";
		}
		for (int r=0;r<=aww;r++) {
            std::cout<<" ";
        }
		gotoxy(x+4,y+1+n);
		adjusttitle(n,1);
    }
    resetColor(colorprev, "adjustShowAll");
}
