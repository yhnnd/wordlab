void changeColorCore(const int r) {
    switch (r) {
        case 7: colorset(lightpurple);	cout<<"7 purple";			break;
        case 6: colorset(lightblue);	cout<<"6 blue";				break;
        case 5: colorset(lightred);		cout<<"5 red";				break;
        case 4: colorset(lightyellow);	cout<<"4 yellow";			break;
        case 3: colorset(lightwhite);	cout << "3 white";			break;
        case 2: colorset(lightcyan);	cout<<"2 cyan";				break;
        case 1: printColorful("1 Colorful");						break;
        case 0: colorset(lightgreen);	cout<<"0 green";			break;
        default:						cout<<"error";				break;
    }
}


void changeColor(const int x, const int y, int *ColorNum) {
    int n = *ColorNum;
    char key;
    for(;;) {
        clearline(x, y);
        for (int r = 0; r <= 7; r++) {
            colorset(lightwhite);
            if (n == r) {
                cout<<"(";
            } else {
                cout<<" ";
            }
            changeColorCore(r);
            colorset(lightwhite);
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


string getChineseColorCommandByNumber(const int d) {
    if (d == 0) {
        return "grn-";//GREEN
    } else if(d == 1) {
        return "clrful-";//COLORFUL
    } else if(d == 2) {
        return "cyn-";//CYAN(scan Mode)
    } else if(d == 3) {
        return "wte-";//WHITE
    } else if(d == 4) {
        return "ylw-";//YELLOW
    } else if(d == 5) {
        return "red-";//RED
    } else if(d == 6) {
        return "blu-";//BLUE
    } else if(d == 7) {
        return "pnk-";//PINK
    }
    return "";
}