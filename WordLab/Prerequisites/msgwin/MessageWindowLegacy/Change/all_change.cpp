void MessageWindow::SelectFrame(int x, int y, int width, const char *msg, const int lineMax, const int lineCharMax) {
    colorrecord(colorprev);

    Frame(0, x, y, width, msg, lineMax, lineCharMax);

    for (int lineNo = 0; lineNo < lineMax; ++lineNo) {
        gotoxy(x + 5, y + 1 + lineNo);
        if (_background) {
            ColorfulB(strsum(msg + lineNo * lineCharMax));
        } else {
            Colorful(strsum(msg + lineNo * lineCharMax));
        }
        const char * line = msg + lineNo * lineCharMax;
        bsvlineDisableColors(line, std::min(width - 1, lineCharMax));
    }
    colorreset(colorprev);
}


void MessageWindow::SelectShowChange(int x,int y,int r1,int r2) {
    int r;
    bool flag = 1;
    if (r1 > r2) {
        std::swap(r1, r2);
        flag = 0;
    }

    for (r = r1 + 1; r < r2; r++) {
        gotoxy(x, y + r);
        if (flag) {
            printf("| ^");
        } else {
            printf("| v");
        }
    }
    gotoxy(x, y + r1);
    if (flag) {
        printf("<--");
    } else {
        printf("-->");
    }
    gotoxy(x, y + r2);
    if (flag) {
        printf("-->");
    } else {
        printf("<--");
    }
}


int MessageWindow::Select(int x,int y,int max,int lastpos, const char * pattern1, const char * pattern2, const char * pattern3) {
    int currentPos = lastpos;
    char key;
    for (;;) {
//        Select Erase
        for (int i = 0; i < max; ++i) {
            gotoxy(x, y  + i);
            std::cout << pattern1;
        }
//        Select Show
        gotoxy(x, y + currentPos);
        if (currentPos < max) {
            std::cout << pattern2;
        } else {
            std::cout << pattern3;
        }

        key = getch();

        if (key == 13 || key == 10) {
            break;
        } else if(key=='w'||key=='W'||key=='-') {
            --currentPos;
        } else if(key=='s'||key=='S'||key=='d'||key=='D'||key=='+') {
            ++currentPos;
        } else {
            return -1;
        }
        if (_LoopLock) {
            roll(currentPos, currentPos, 0, max - 1);
        } else {
            limit(currentPos, currentPos, 0, max - 1);
        }
    }
    return currentPos;
}


void MessageWindow::Selectup(char *msg, const int max, const int width, const int r1, const int r2) {
    char *temp = (char *) calloc(width, sizeof (char));
    strncpy(temp, msg + r1 * width, width);
    for (int r = r1; r > r2; r--) {
        strncpy(msg + r * width, msg + (r - 1) * width, width);
    }
    strncpy(msg + r2 * width, temp, width);
}


void MessageWindow::Selectdown(char *msg, const int max, const int width, const int r1, const int r2) {
    char *temp = (char *) calloc(width, sizeof (char));
    strncpy(temp, msg + r1 * width, width);
    for (int r = r1; r < r2; r++) {
        strncpy(msg + r * width, msg + (r + 1) * width, width);
    }
    strncpy(msg + r2 * width, temp, width);
}


void MessageWindow::Change(int x,int y,int width,char *msg,int max,int w) {
    int r1, r2;

    SelectFrame(x, y, width, msg, max, w);

    int xSelector = x + 1, ySelector = y + 1;

#ifdef __APPLE__
    xSelector = x + 2;
#endif

    r1 = Select(xSelector, ySelector, max, 0, "[=]", "[A]", "[0]");

    if (r1 == -1) {
        status("msgwin: change cancelled");
        goto end;
    }

    r2 = Select(xSelector, ySelector, max, r1, "[=]","[B]","[0]");

    if (r2 == -1) {
        status("msgwin: change cancelled");
        goto end;
    }

    if (r1 > r2) {
        Selectup(msg, max, w, r1, r2);
    } else {
        Selectdown(msg, max, w, r1, r2);
    }

    SelectFrame(x, y, width, msg, max, w);

    SelectShowChange(xSelector, ySelector, r1, r2);

    getch();

    end:
    Frame(0, x, y, width, msg, max, w);
}
