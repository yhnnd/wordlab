int MessageWindow::Select(int x,int y,int n,int lastpos, const char * pattern1, const char * pattern2, const char * pattern3) {
    int r;
    char key;
    for (r=lastpos;;) {
        SelectErase(x,y,n,pattern1);
        SelectShow(x,y,r,n,pattern2,pattern3);
        key = getch();
        if (key == 13 || key == 10) {
            break;
        } else if(key=='w'||key=='W'||key=='-') {
            r--;
        } else if(key=='s'||key=='S'||key=='d'||key=='D'||key=='+') {
            r++;
        } else {
            return n-1;
        }
        if (_LoopLock) {
            roll(r,r,1,n-1);
        } else {
            limit(r,r,1,n-1);
        }
    }
    return r;
}
