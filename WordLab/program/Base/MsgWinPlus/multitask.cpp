int chooseFromMenu (COORD displayPos, const int width, const vector<string> menu) {
    int usersChoice = 1;
    const int outerWidth = width + 8;
    const int max = menu.size();
    const string format = " [%d] %" + toString(width) + "s  ";
    char ch = 0;
    for (;;) {

        gotoxy(displayPos);
        setForegroundColorAndBackgroundColor("blu-", "-blu");
        std::cout << "+" << std::right << std::setfill('-') << std::setw(outerWidth) << "+" << endl;

        for (int i = 0; i < max; ++ i) {
            string line = menu[i];
            const auto delimPos = line.find(",");
            if (delimPos != std::string::npos) {
                line = line.substr(0, delimPos);
            }
            gotoxy(displayPos.X, displayPos.Y + i + 1);
            setForegroundColorAndBackgroundColor("blu-", "-blu");
            printf("|");
#ifdef __APPLE__
            if (displayPos.X > 0) {
                gotoxy(displayPos.X + width + 8, displayPos.Y + i + 1);
            } else {
                gotoxy(displayPos.X + width + 9, displayPos.Y + i + 1);
            }
#else
            gotoxy(displayPos.X + width + 8, displayPos.Y + i + 1);
#endif
            printf("|");
            if (usersChoice == i) {
                setForegroundColorAndBackgroundColor("blk-", "-wte");
            } else {
                setForegroundColorAndBackgroundColor("wte-", "-blk");
            }
#ifdef __APPLE__
            if (displayPos.X > 0) {
                gotoxy(displayPos.X + 1, displayPos.Y + i + 1);
            } else {
                gotoxy(displayPos.X + 2, displayPos.Y + i + 1);
            }
#else
            gotoxy(displayPos.X + 1, displayPos.Y + i + 1);
#endif
            printf(format.c_str(), i, line.c_str());
        }
        gotoxy(displayPos.X, displayPos.Y + max + 1);
        setForegroundColorAndBackgroundColor("blu-", "-blu");
        std::cout << "+" << std::right << std::setfill('-') << std::setw(outerWidth) << "+";
        std::cout << std::setfill(' ') << std::left;
        setForegroundColorAndBackgroundColor("wte-", "-blk");
        gotoxy(displayPos.X, displayPos.Y + max + 2);
        printf("your input: '%c'", ch);

        ch = getch();

        if (ch == 8 || ch == 127 || ch == 27) {
            usersChoice = -1;
            break;
        } else if (ch == 13 || ch == 10) {
            break;
        } else if (ch == 'w' || ch == 'a') {
            --usersChoice;
        } else if (ch == 's' || ch == 'd') {
            ++usersChoice;
        }
        if (usersChoice < 0) {
            usersChoice = 0;
        } else if (usersChoice >= max) {
            usersChoice = max - 1;
        }
    }
    return usersChoice;
}


vector<string> getVectorOfString(const char * ptr, const int lineMax, const int lineCharMax) {
    vector<string> vs;
    for (int i = 0; i < lineMax; ++i) {
        string line = ptr + i * lineCharMax;
        if (line.length() > lineCharMax) {
            line = line.substr(0, lineCharMax);
        }
        vs.push_back(line);
    }
    return vs;
}


int multitask(int x,int y,int width,char Menu[][LINEMAX],int T=0,int n=0,bool backcolor = 0) {
	int a = -1;
	bool backcolorold = MessageWindow.SetBackground(backcolor);
#if defined(_WIN32)
	if (version==OLD) {
	    if (T==0) {
            MessageWindow.Show(x,y,width,&Menu[0][0],0,LINEMAX);
        } else {
            MessageWindow.Frame(0,x,y,width,&Menu[0][0],0);
        }
		a =  MessageWindow.Switch (x,y,width,&Menu[0][0],0,LINEMAX,n);
	} else if(version==NEW) {
        a = MessageBlock.Switcher(Menu);
    }
#elif defined(__APPLE__)
    const int maxlength = MaxLength(&Menu[0][0],LINEMAX);
    if (version==OLD) {
        if (T==0) {
            MessageWindow.Show(x,y,width,&Menu[0][0],0,LINEMAX);
        } else {
            MessageWindow.Frame(0,x,y,width,&Menu[0][0],0);
        }
        a =  MessageWindow.Switch (x,y,width,&Menu[0][0],0,LINEMAX,n);
    } else if (version == NEW) {
        a = MessageBlock.Switcher(Menu);
    } else if (version == COMPACT) {
        const COORD pos = {static_cast<short>(x), static_cast<short>(y)};
        a = chooseFromMenu(pos, width, getVectorOfString(&Menu[0][0], maxlength, LINEMAX));
    }

//    if (a >= 0 && a < maxlength) {
////        popup("<grn->(your choice:) ", toString(a), -1);
//    } else {
////        popup("<red-> (error) <ylw->(\\(illegal choice\\)) ", string("\'") + toString(a) + "\'", -1);
//    }
#endif
	MessageWindow.SetBackground(backcolorold);
	return a;
}
