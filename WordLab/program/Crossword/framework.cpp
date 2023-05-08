int CrosswordFramework(){
	clearScreen();
	colorset(lightwhite);

	string folder = CrosswordDataFolder;
	string folder2 = CrosswordSelectFolder(folder);

	if(folder2.empty()) {
        return errorlog("CrosswordFramework()","no game folder in",folder);
    }

	int w=12, h=8;

	ifstream in(folder2+"/board_info.dat");

	if(in.is_open()){
		in.ignore(1024,'=');
		in>>w;
		in.ignore(1024,'=');
		in>>h;
	} else {
        return errorlog("CrosswordFramework()","no board data file in",folder2);
    }

	in.close();

    const char c = popup("load previous progress?", -1);
	bool LoadPrev= (c == 13 || c == 10);

	crossword Crossword(folder2,LoadPrev,4,4,2,w,h);

	if(!Crossword.Available()) {
        return errorlog("CrosswordFramework()","no game data in",folder2);
    }

	//Crossword.check({"pineapple","elbow","apples","pear","bowl","ear","horse","arrow","sow"});

	char key = 13;
    int n = 0;

	popup("Answer[A/W/S/D/Enter] Rotate[Q/R]", 0);

	for (;;) {
        if (key != 'q' && key != 'r' && key != 13) {
            fflush(stdin);
            cin.clear();
            cin.sync();
            key = getch();
        }
        if (key == '0' || key == 8 || key == 27 || key == 127) {
            break;
        }
        if (key == 'q') {
            // anticlockwise rotate
            Crossword.rotate(-1);
            n = -1;
        } else if (key == 'r') {
            // clockwise rotate
            Crossword.rotate(1);
            n = -1;
        }
        Crossword.show();
        Crossword.info(key);
        key = 0;
        n = Crossword.SelectWord(key, n);
        if (n != -1) {
            Crossword.AnswerWord(n);
            Crossword.save();
            Crossword.show();
            Crossword.info(key);
            Crossword.showSelectedWord(n);
            key = 0;
        }
	}
	return 0;
}
