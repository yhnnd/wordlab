// display a bsv file
int bsvlines(char **msgs,const int max,const int width,const char *folder,const int x,const int y,void *spptr) {
    PKC brcmdbegin = "<";
    PKC brcmdend = ">";
    PKC fieldbegin = "(";
    PKC fieldend = ")";
    PKC tokens_term = ";";

	char key;
	bool enterKeyPressed = false, bsvStylesDisabled = false;
	int i = 0, maxLabels = 0;
    static int chosenLabel = 0;
	for(;;) {
		// display bsv file
        int currentY = y;
		for( i = 0; i < max; i++ ) {
			gotoxy(x, currentY++);
//            std::cout << "bsv line: " << clock();
            if (bsvStylesDisabled == true) {
                setForegroundColorAndBackgroundColor("red-", "-wte");
                bsvlineDisableColors(msgs[i], width, brcmdbegin, brcmdend, fieldbegin, fieldend, tokens_term);
            } else {
                bsvline(msgs[i], width, brcmdbegin, brcmdend, fieldbegin, fieldend, tokens_term, (scriptprocessor *) spptr);
            }
			if (msgs[i][strlen(msgs[i])-1] == '\n') {
                currentY++;
            }
		}


		gotoxy(x, y);// reset cursor
        currentY = y;

		// get num of labels
		for( i = 0, maxLabels = 0; i < max; i++ ) {// enterKeyPressed is false
			maxLabels = bsvLineLabels(msgs[i], 0, maxLabels,0,folder,x,y,width,"wte-gry","wte-blu","<",">","(",")",spptr);
		}

        // highlight or enter the label selected
        int currentLabel = 0;
        for (i = 0; i < max; i++) {
            gotoxy(x, currentY++);
            currentLabel = bsvLineLabels(msgs[i], chosenLabel, currentLabel,enterKeyPressed,folder,x,y,width,"wte-gry","wte-blu","<",">","(",")",spptr);
            if (currentLabel < 0) {
                return -1;
            }
            if (msgs[i][strlen(msgs[i])-1]=='\n') {
                gotoxy(1, currentY++);
            }
        }

        enterKeyPressed = 0;

        popup("#setMode('y++')");
        popup("#offsetY=0;");
        popup("#enableBorderTop=true;");
        popup("BSV LINES: label chosen " + toString(chosenLabel), 0);
        popup("BSV LINES: Press [ENTER] or [W↑] [A←] [S↓] [D→] to switch labels.", 0);
        popup("#setMode('y=1')", 0);

        // display bsv file name
        colorrecord(colorPrev);
        gotoxy(x, y - 1);
        setForegroundColorAndBackgroundColor("wte-", "-blu");
        printf("%s", folder);
        colorreset(colorPrev);

		key = getch();
		if (key == BIOSKEY) {
			key = getch();
			if(key==UP) {
                key = 'w';
            } else if(key==DOWN) {
                key = 's';
            } else if(key==LEFT) {
                key = 'a';
            } else if(key==RIGHT) {
                key = 'd';
            }
		}// CANNOT FOLLOW AN 'ELSE'
		if(key == 13) {
            enterKeyPressed = true;
        } else if (key == 8 || key == 127 || key == 27) {
//			clearscreen(0,0,ScreenX,max+2);
			return -1;//exit
		} else if(key=='w'||key=='a') {
            chosenLabel--;
        } else if(key=='s'||key=='d'||key==32) {
            chosenLabel++;
        }
		limit(chosenLabel,chosenLabel,0,maxLabels);
		gotoxy(1, y);// reset cursor
	}
	return 0;
}
