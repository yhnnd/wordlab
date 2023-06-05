void changeColorCore(const int r) {
    if (r >= 0 && r < definitionColorSpectrum.size()) {
        setForegroundColorAndBackgroundColor(definitionColorSpectrum[r] + "-", "-blk");
        printf("%d %s", r, definitionColorNames[r].c_str());
    }
}


void changeColor(const int x, const int y, int *ColorNum) {
    int n = *ColorNum;
    char key;
    for(;;) {
        clearline(x, y);
        for (int r = 0; r <= 7; r++) {
            setColor(lightwhite, "changeColor");
            if (n == r) {
                cout<<"(";
            } else {
                cout<<" ";
            }
            changeColorCore(r);
            setColor(lightwhite, "changeColor");
            if (n == r) {
                cout<<")";
            } else {
                cout<<" ";
            }
        }
        key = getch();
        if (key == 13 || key == 10) {
            break;
        } else if (key==8||key==127||key==27||key=='r'||key=='R') {
            return;
        } else if (key=='a'||key=='A'||key=='w'||key=='W') {
            omit(n, n, -1, 2);
        } else if (key=='d'||key=='D'||key=='s'||key=='S') {
            omit(n, n, 1, 2);
        }
        roll(n, n, 0, 7);
    }
    *ColorNum = n;
}


void setChineseColor(int * ColorFlags) {
    int i = 0;
    for (i = 0; i < 2; ++i) {
        clearline(0, i * 2);
        printf("Please choose a color for <translation %d>", i);
        changeColor(0, i * 2 + 1, ColorFlags + i);
    }
    clearline(0, i * 2);
    printf("done");
}


std::string getChineseColorCommandByNumber(const int d) {
    if (d >= 0 && d < definitionColorSpectrum.size()) {
        return definitionColorSpectrum[d] + "-blk";
    }
    return "";
}