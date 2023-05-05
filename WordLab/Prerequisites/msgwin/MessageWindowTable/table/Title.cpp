void Table::Title(int x,int y,int width,int Total) {
	int margin=3;
	char TableTitle[4][LINEMAX] = {
            "All",
            "ORDER   CLASS    NAME    NUMBER    INFORMATION",
            "Choose Class",
            "Control Panel"
    };
//	loadmsg((char*)TableTitle,TableTitleRoute,4,LINEMAX,1,1);
	colorset(backlightwhite);
	clearline(x,y+0,width+2*margin);
	std::cout<<TableTitle[0];

	for(int r = 1; r <= 8; r++) {
        std::cout << std::right << std::setw(width/9) << r;
    }
	clearline(x,y+1,width+2*margin);

	std::cout<<TableTitle[1];

	Frame(0, x, y + 2, width, Total + 2, 0);

	colorset(backdarkwhite);
	gotoxy(x+6,y+1+Total+2);
	std::cout<<TableTitle[2];
	gotoxy(x+6,y+1+Total+3);
	std::cout<<TableTitle[3];
	gotoxy(x+6,y+Total+5);
    colorset(lightwhite | backlight | backblue);
	std::cout<<"row=["<<18<<"] ";
	std::cout<<"col=["<<4<<"] ";
	std::cout<<"col-volume=["<<64<<"]";
}
