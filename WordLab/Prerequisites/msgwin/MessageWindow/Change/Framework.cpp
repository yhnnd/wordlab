void MessageWindow::Change(int x,int y,int width,char *msg,int max,int w){
	int r, r1, r2;
	char s[LINEMAX];
	r = SelectFrame(x, y, width, msg, max, w);
	r1 = Select(x+1, y+1, r, 1, "[=]", "[A]", "[0]");
	if (r1 == r-1) {
        status("msgwin: change cancelled");
        goto end;
    }
	r2 = Select(x+1,y+1,r,r1,"[=]","[B]","[0]");
	if (r2 == r-1) {
        status("msgwin: change cancelled");
        goto end;
    }
	if (r1 > r2) {
        Selectup(msg,max,w,r1,r2,r,s);
    } else {
        Selectdown(msg,max,w,r1,r2,r,s);
    }
	SelectFrame(x,y,width,msg,max,w);
	SelectShowChange(x+1,y+1,r1,r2);
	for(;;) {
        if(kbhit()) {
            break;
        }
    }
	end:
	Frame(0,x,y,width,msg,0);
}
