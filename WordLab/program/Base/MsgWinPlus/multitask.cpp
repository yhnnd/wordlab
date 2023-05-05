int multitask(int x,int y,int width,char Menu[][LINEMAX],int T=0,int n=0,bool backcolor=0) {
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
        a = 1;
        const int outerWidth = width + 8;
        const string format = " [%d] %" + toString(width) + "s  ";
        char ch = 0;
        for (;;) {
            gotoxy(x, y);
            setForegroundColorAndBackgroundColor("blu-", "-blu");
            std::cout << "+" << std::right << std::setfill('-') << std::setw(outerWidth) << "+" << endl;
            const int max = MaxLength(&Menu[0][0],LINEMAX);
            for (int i = 0; i < max; ++ i) {
                string line = Menu[i];
                const auto delimPos = line.find(",");
                if (delimPos != std::string::npos) {
                    line = line.substr(0, delimPos);
                }
                setForegroundColorAndBackgroundColor("blu-", "-blu");
                printf("|");
                if (a == i) {
                    setForegroundColorAndBackgroundColor("blk-", "-wte");
                } else {
                    setForegroundColorAndBackgroundColor("wte-", "-blk");
                }
                printf(format.c_str(), i, line.c_str());
                setForegroundColorAndBackgroundColor("blu-", "-blu");
                printf("|\n");
            }
            setForegroundColorAndBackgroundColor("blu-", "-blu");
            std::cout << "+" << std::right << std::setfill('-') << std::setw(outerWidth) << "+" << endl;
            std::cout << std::setfill(' ') << std::left;
            setForegroundColorAndBackgroundColor("wte-", "-blk");
            printf("your input: '%c'", ch);
            ch = getch();
            if (ch == 8 || ch == 127 || ch == 27) {
                a = -1;
                break;
            } else if (ch == 13 || ch == 10) {
                break;
            } else if (ch == 'w' || ch == 'a') {
                --a;
            } else if (ch == 's' || ch == 'd') {
                ++a;
            }
            if (a < 0) {
                a = 0;
            } else if (a >= max) {
                a = max - 1;
            }
        }
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
