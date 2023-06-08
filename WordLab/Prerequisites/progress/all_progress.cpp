prerequisites::progressBar::progressBar(const int threadMax, const bool interrupt, const bool ask) {
    this->setThread(threadMax);
    this->setInterrupt(interrupt);
	this->_AskBeforeQuit = ask;
}

void prerequisites::progressBar::line(int x, int y, int nPrev, int n, char s, WORD color){
	int r = nPrev;
	gotoxy(x + r, y);
	recordColor(colorprev, "progressBar::line");
    setColor(color, "progressBar::line");
	for (; r < n; r++) {
        std::cout << s;
    }
    resetColor(colorprev, "progressBar::line");
}

int prerequisites::progressBar::show(int x, int y, int thread, int n, int width, WORD back, WORD fore) {
	if (n > 0 && nprev[thread] == n) {
        return 0;
    } else if (n == 0) {
        line(x,y,0,width,'-',back);
    } else {
        line(x,y,nprev[thread],n,'*',fore);
    }
    nprev[thread] = n;
    if (_AllowInterrupt) {
	    if (kbhit()) {
		    key = getch();
			if (this->_AskBeforeQuit) {
			    if (MessageWindow.alert("cancel?",2,ScreenX/4,ScreenY/4,20,2,6)==1) {
                    return -1;
                }
            } else {
                return -1;
            }
		}
	}
    return 0;
}

void prerequisites::progressBar::setInterrupt(const bool n) {
	this->_AllowInterrupt = n;
}

void prerequisites::progressBar::setThread(const int n) {
	this->nprev = (int *) malloc(sizeof(int[n]));
}


char prerequisites::fatalError(int delayperiod) {
	int r,w=30,x=(ScreenX-w)/2,y=6,max=10;
	progressBar bar(max, true, false);
	for (;;) {
	    for(r=0;r<max;r++) {
            if(bar.show(x,y+r,r,0,w,bothred,bothlightred)==-1) {
                return 0;
            }
        }
	    for(r=0;r<max;r++) {
            if(bar.show(x,y+r,r,rand()%(w+1),w,bothred,bothlightred)==-1) {
                return 0;
            }
        }
        char ch;
#ifdef _WIN32
        ch = wait(delayperiod,10,1,0,0);
#elifdef __APPLE__
        ch = getch();
#endif
		if (ch) {
            return ch;
        }
	}
}


int prerequisites::confirmationBar(int x, int y, int width, int delay){
	int i = 0;
	progressBar bar(1, 1, 1);
	for (i = 0; i <= width; i++) {
		if (bar.show(x,y,0,i,width)==-1) {
            break;
        }
		if (delay>0&&wait(delay,1,0)&&MessageWindow.alert("cancel?",2,ScreenX/4,ScreenY/4,20,2,6)==1) {
            break;
        }
    }
	return (i>width)?0:-1;
}
