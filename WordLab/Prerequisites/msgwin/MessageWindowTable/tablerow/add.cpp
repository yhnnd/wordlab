int tablerow::setcol(int x, int y, char *col) {

#ifdef __APPLE__
    x = x + 1;
#endif

	gotoxy(x, y);
	if (col[0]) {
		printf("%s", col);
		gotoxy(x,y);
	}
    fflush(stdin);
	scanf("%s[^\n]", col);
    fflush(stdin);
    return 0;
}

int tablerow::Add(int x,int y,int width) {
	char msg[3][LINEMAX]={
            "name  value  info",
            " ",
            "  1   2   3   4   5   6   7   8   9  10  11  12"
	};
	MessageWindow.Frame(0,x,y,width,&msg[0][0],3);
	setcol(x+4,y+2,col[1]);
	setcol(x+4+1+strlen(col[1]),y+2,col[2]);
	setcol(x+4+2+strlen(col[1])+strlen(col[2]),y+2,col[3]);
//	itoa(MessageWindow.ConfirmSwitch(12,x+4,y+2,width+5,1),col[0],10);
    return 0;
}
