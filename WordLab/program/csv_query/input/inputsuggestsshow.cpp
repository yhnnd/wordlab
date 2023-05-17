int inputsuggestsshow(char *msg,char *keywords,int n,int lth,int maxresult,const COORD pos) {
	int i = 0, r = 0;
    colorrecord(colorPrev);
    setForegroundColorAndBackgroundColor("blk-", "-gry");
	clearscreen(pos.X, pos.Y + 1, lth, maxresult);
	for(i=0,r=0; i<n&&r<maxresult; i++) {
		if(strindex(keywords+i*lth,msg)>=0) {
            setForegroundColorAndBackgroundColor("blk-", "-ylw");
			clearline(pos.X, pos.Y + 1 + r, lth);
			printf("%s", keywords + i * lth);
			r++;
		}
	}
    colorreset(colorPrev);
    return 0;
}
