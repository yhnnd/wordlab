void index(char *msg, const int x, const int y, WORD color=lightwhite, int BeginPoint = 0) {
	int r;
	char c;
	for (r=BeginPoint;;) {
        if (r < 0) {
            strclr(msg);
            return;
        } else if ((c=getch()) == 13) {
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
	    indexCore(msg,x,y,color);
    }
}
