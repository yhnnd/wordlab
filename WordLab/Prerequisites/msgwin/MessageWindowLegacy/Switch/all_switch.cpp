// "pointer"
int MessageWindow::Pointer(const int x, const int y, const int max, const int n, const int nprev, const bool flag0 = true, const bool flag1 = true) {
    colorrecord(colorprev);
    if (nprev>=0&&nprev<max) {
        colorset(bothdarkwhite);
        gotoxy(x,y+nprev);
#ifdef __APPLE__
        movexy(1, 0);
#endif
        std::cout<<"   ";
    }
    if (flag1==true) {
        colorset(bothlightgreen);
        gotoxy(x,y+max-2);
#ifdef __APPLE__
        movexy(1, 0);
#endif
        std::cout<<"-1 ";
    }
    if (flag0==true) {
        colorset(bothlightred);
        gotoxy(x,y+max-1);
#ifdef __APPLE__
        movexy(1, 0);
#endif
        std::cout<<" 0 ";
    }
    if (n>=0&&n<max) {
        colorset(bothlightyellow);
        gotoxy(x,y+n);
#ifdef __APPLE__
        movexy(1, 0);
#endif
        std::cout<<"-->";
    }
    colorreset(colorprev);
    return getch();
}


// "Roller"
void MsgWinSwiShwChsCore(int radius,int x,int y,int width,const char *what){
    colorrecord(colorprev);
    switch(abs(radius)) {
        case  0:
            setForegroundColorAndBackgroundColor("wte-", "-blu");
            break;
        case  1:
            setForegroundColorAndBackgroundColor("#wte", "-blk");
            break;
        case  2:
            setForegroundColorAndBackgroundColor("#blu-", "-blk");
            break;
        default:
            setForegroundColorAndBackgroundColor("red-", "-blk");
            break;
    }
    clearline(x, y, width);
    bsvlineDisableColors(what, width, "<", ">", "(", ")", ",;");
    colorreset(colorprev);
}

void MsgWinSwiShowChoosed(int radius,int x,int y,int width,int n,const char *what,int max,int w){
    for(int r=-radius;r<=radius;r++){
        MsgWinSwiShwChsCore(r,x,y+r,width,what+((n+r+max)%max)*w);
    }
}


// "Search"
int MessageWindow::SearchCore(int showpos,int x,int y,int width,const char *msg,int max,int w,char *keyword) {

    Frame(0, x, y, width, msg, max);

    if (keyword[0] == '\0') {
        return -1;
    }

    colorrecord(colorprev);

    gotoxy(x + 5 + bsvmaxlth(msg+showpos*w,"</",">/","()",",;"), y + 1 + showpos);
    printf("%s", keyword);

    int r, n = -1;
    for (r = 0; r < max; r++) {
        if (strindex(msg+r*w, keyword) != -1) {
            gotoxy(x + 5, y + 1 + r);
            bsvlineDisableColors(msg+r*w,width,"</","/>","(",")",",;");
            n = (n > 0) ? n: r;
        }
    }
    colorreset(colorprev);
    return n;
}


int MessageWindow::Search(int showpos,int x,int y,int width,const char *msg,int max,int w) {
    char keyword[w], c;
    int r, n= -1;
    strclr(keyword);
    for (r=0; (c = getch()) != 13 && c != 10;) {
        if (c == 8 || c == 127) {
            keyword[r] = 0;
            keyword[--r] = 0;
        } else {
            keyword[r++] = c;
            keyword[r+1] = 0;
        }
        if (r < 0) {
            return -2;
        }
        n = SearchCore(showpos,x,y,width,msg,max,w,keyword);
    }
    return n;
}



void MessageWindow::SwitchLoop(int x,int y,int width,const char *what,int max,int w,int *n) {
    roll(*n, *n, 0, max - 1);

#ifdef __APPLE__
    if (x == 0) {
        x = x + 1;
    }
#endif

    if(this->_background) {
        MsgWinSwiShowChoosed(0, x + 4, y + max + 1, width, *n, what, max, w);
    } else if(max<=8) {
        MsgWinSwiShowChoosed(1, x + width + 6, y + max + 1,width,*n,what,max,w);
    } else {
        MsgWinSwiShowChoosed(2, x + width + 6, y + max + 1,width,*n,what,max,w);
    }
}



int MessageWindow::Switch(int x,int y,int width,char *what,int max,int w,int n) {
    int xPointer = x + 1;
#ifdef __APPLE__
    xPointer = x;
#endif

    char r, nprev = -1;
    if(max<=0) {
        max = MaxLength(what,w);
    }
    for(;;) {
        begin:
        limit(n,n,0,max-1);
        r = Pointer(xPointer, y + 1,max,n,nprev);
        nprev = n;
        if (r == 13 || r == 10) {
            break;
        } else if(r=='r'||r=='R'||r==KEY_DELETE||r==KEY_ESC||r==MAC_OS_KEY_DELETE) {
            return -1;
        } else if(r=='l'||r=='L') {
            deny(_LoopLock,_LoopLock);
        } else if(r=='i'||r=='I') {
            Change(x,y,width,what,max,w);
        } else if(r=='n'||r=='N') {
            bsvviewer("buf.bsv");
            Frame(0,x,y,width,what,max);
        } else if(r=='e'||r=='E'||r=='w'||r=='W') {
            n--;
        } else if(n<max-1||_LoopLock) {
            n++;
        }
        if(_LoopLock) {
            SwitchLoop(x,y,width,what,max,w,&n);
        }
    }
    if (!_background) {
        Highlight(what+n*w);
    }
    if (n == 0) {
        if ((n = Search(0,x,y,width,what,max,w))==-2) {
            goto begin;
        }
    }
    return n;
}


int MessageWindow::Switch(int x,int y,int width,std::vector<std::string> what,int n) {
    char c, nprev = -1;
    int max = what.size();
    for(;;) {
        limit(n, n, 0, max - 1);
        c = Pointer(x, y + 1, max, n, nprev);
        nprev = n;
        if (c == 13 || c == 10)  {
            break;
        } else if(c=='r'||c=='R'||c==KEY_DELETE||c==MAC_OS_KEY_DELETE||c==KEY_ESC) {
            return -1;
        } else if(c=='e'||c=='E'||c=='w'||c=='W') {
            n--;
        } else if(n<max-1||_LoopLock) {
            n++;
        }
        if (_LoopLock) {
            roll(n, n, 0, max - 1);
        }
    }
    if (!_background) {
        Highlight(what[n].c_str());
    }
    return n;
}
