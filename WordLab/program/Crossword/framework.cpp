int CrosswordFramework(){
	clearScreen();
	colorset(lightwhite);

	string folder=CrosswordDataFolder;
	string folder2=CrosswordSelectFolder(folder);

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

    const char c = popup("load previous progress?",-1);
	bool LoadPrev= (c == 13 || c == 10);

	crossword Crossword(folder2,LoadPrev,4,4,2,w,h);

	if(!Crossword.Available()) {
        return errorlog("CrosswordFramework()","no game data in",folder2);
    }

	//Crossword.check({"pineapple","elbow","apples","pear","bowl","ear","horse","arrow","sow"});

	int key = 0, n = 0;

	popup("Answer[A] Hint[H] Rotate[Q/R] Settings[S]", 0);

	for (;Crossword.show();) {
		Crossword.info(key);
		Crossword.save();
		if ((key=getch())=='0' || key == 8 || key == 27 || key == 127) {
            break;
        }
		switch (key) {
			case 'a':
            case 13:// Carriage Return
            case 10:// Line Feed
                //answer
				n = Crossword.SelectWord();
				Crossword.AnswerWord(n);
				break;
			case 'h'://hint
				Crossword.hint(n);
				break;
			case 'q'://anticlockwise rotate
				Crossword.rotate(-1);
				break;
			case 'r'://clockwise rotate
				Crossword.rotate(1);
				break;
			case 's'://settings
				Crossword.settings();
				break;
			default:
				break;
			}
	}
	return 0;
}
