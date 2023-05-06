
bool indexerror(){
    bool flag = false;
    FILE *fp1 = fopen(EnglishRoute,"r"), *fp2 = fopen(ChineseRoute,"r");
    if (fp1==NULL||fp2==NULL) {
        cout<<"Index Engine: Data Lost";
        flag = true;
    }
    fclose(fp1);
    fclose(fp2);
    return flag;
}


void indexCore(const std::string msg, int x, int y, WORD color){
    recordxy(pos);
    char wordbase[LINEMAX];

    colorset(color);
    clearscreen(x, y, 60, 10);

    gotoxy(x , y);
    printf("%s", msg.c_str());

    if(!indexerror() && IL) {
        Select(msg.c_str(), wordbase, x, y);
    }
    resetxy(pos);
}


void index(char *msg, const int x, const int y, WORD color, int BeginPoint = 0) {
    int r;
    char c;
    for (r=BeginPoint;;) {
        if (r < 0) {
            strclr(msg);
            return;
        } else if ((c=getch()) == 13 || c == 10) {
            strclr(msg,strlen(msg));
            return;
        } else if (c == 8 || c == 127 || c == 27) {
            if (r > 0) {
                strclr(msg,r--);
            } else {
                strclr(msg);
                return;
            }
        } else {
            msg[r++]=c;
        }
        strclr(msg,r);
        indexCore(msg, x, y, color);
    }
}
