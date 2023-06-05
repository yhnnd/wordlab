bool indexerror() {
    bool flag = false;
    FILE *fp1 = fopen(EnglishRoute,"r"), *fp2 = fopen(ChineseRoute,"r");
    if (fp1 == NULL || fp2 == NULL) {
        cout << "Index Engine: Data Lost";
        flag = true;
    }
    fclose(fp1);
    fclose(fp2);
    return flag;
}


void indexCore(const std::string msg, int x, int y, WORD color) {
    recordColor(colorPrev, "indexCore record");

    if(!indexerror() && IL == true) {
        setColor(color, "indexCore set");
        clearScreen(x, y, 60, 10);
        char wordbase[LINEMAX];
        Select(msg.c_str(), wordbase, x, y);
    }

    setForegroundColorAndBackgroundColor("wte-", "-blk");
    clearline(x, y, 60);
    printf("%s", msg.c_str());

    resetColor(colorPrev, "indexCore reset");
}


void index(char *msg, const int x, const int y, const WORD color, const int BeginPoint) {
    int r = BeginPoint;
    char c;

    indexCore(msg, x, y, color);

    for (;;) {
        if (r < 0) {
            strclr(msg);
            return;
        } else if ((c = getch()) == 13 || c == 10) {
            strclr(msg, strlen(msg));
            return;
        } else if (c == 8 || c == 127 || c == 27) {
            if (r > 0) {
                strclr(msg,r--);
            } else {
                strclr(msg);
                return;
            }
        } else {
            msg[r++] = c;
        }
        strclr(msg,r);
        indexCore(msg, x, y, color);
    }
}
