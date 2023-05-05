void MessageWindow::ListSwitchBlock(int x,int y,int n,int r,int width,int height,char c){
    if(n<=0||r<=0) return;
    int rx,ry;
    if(width<2) {
        width=2;
    }
    if(height<1) {
        width=1;
    }
    for(ry=0;ry<height;ry++){
        for(rx=0;rx<width;rx++){
            gotoxy(x+rx+(r-1)*width,y+ry);
            std::cout << c;
        }
    }
}


void MessageWindow::ListSwitchErase(int x,int y,int n,int width,int height){
    int r;
    colorset(lightwhite);
    for(r=1;r<=n;r++) {
        ListSwitchBlock(x,y,n,r,width,height,' ');
    }
}


int MessageWindow::ListSwitch(int N,int x,int y,int width){
    int r,rY,rX;
    char key;
    for (r=1;;) {
        ListSwitchErase(x,y,N,width/N,1);
        ColorfulAll(r);
        ListSwitchBlock(x,y,N,r,width/N,1,'*');
        ColorfulB(r);
        printf("\b\b%-2d", r);
        colorset(lightwhite);

        key = getch();

        if (key == 13 || key == 10) {
            break;
        } else if(key=='0'||key=='r'||key==27||key==8 || key == 127) {
            return 0;
        } else if(key=='A'||key=='a'||key=='W'||key=='w') {
            r--;
        } else {
            r++;
        }
        limit(r,r,1,N);
    }
    return r;
}


int MessageWindow::ListSwitch(int rprev,int N,int x,int y,int width){
    int  rY, rX, r = rprev;
    char key;
    ListSwitchErase(x,y,N,width/N,1);
    ColorfulAll(r);
    ListSwitchBlock(x,y,N,r,width/N,1,'*');
    ColorfulB(r);
    printf("\b\b%-2d", r);
    colorset(lightwhite);

    key = getch();

    if (key == 13 || key == 10) {
        return r;
    } else if (key=='0' || key=='r' || key == 27 || key == 8 || key == 127) {
        return -1;
    } else if(key=='A'||key=='a'||key=='W'||key=='w') {
        r--;
    } else if(key=='D'||key=='d'||key=='S'||key=='s') {
        r++;
    }
    return r;
}
