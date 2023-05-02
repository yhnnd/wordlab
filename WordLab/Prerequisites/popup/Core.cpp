
char popupcore(const std::string msg, const int life, const int x, const int y, const int width, popupConfigs& configs) {
	char key = 0;
	// record previous status
	colorrecord(colorprev);
	recordxy(pos);
	// display message

    if (configs.ShowBorderTop == true || configs.Mode == "y=1") {
        MessageWindow.Edge(x, y - 1, width);
		if (configs.Mode == "y++") {
			configs.ShowBorderTop = false;
		}
    }
	MessageWindow.Line(x,y,width,msg.c_str(),0);
	MessageWindow.Edge(x,y+1,width);
	colorset(lightwhite);
	// wait for response
	if (life > 0) {
#ifdef _WIN32
		time_t BeginTime=clock();
		while(!kbhit()) {
	    	if(clock()-BeginTime>life) goto BreakWait;
	    	gotoxy(x+width,y);
			//show time remains
	    	std::cout<<1+(life-(clock()-BeginTime))/1000<<"s";
	    	Sleep(10);
		}
#endif
		key = getch();
		BreakWait:
		MessageWindow.Erase(x,0,width,y);
	} else if (life < 0) {
        key = getch();
    }
	// reset
	resetxy(pos);
	colorreset(colorprev);
	// write history
	if (configs.RecordEnabled) {
#ifndef _data_dir
	    std::ofstream fout("buf.bsv",std::ios::app);
#else
	    std::ofstream fout(_data_dir"buf.bsv",std::ios::app);
#endif
		if(fout.is_open()) fout<<msg.c_str()<<std::endl;
		fout.close();
	}
//    printf("\nInput key is [%c] (%d)\n", key, key);
	return key;
}
