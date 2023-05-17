int messageblock::Search(char what[][LINEMAX],int N) {
	int r, n = 0, nprev = N, lth = 30;
	char c,keyword[lth];
	strclr(keyword);
	colorrecord(colorprev);
	colorset(bothlightwhite);
	clearline(x+(width-lth)/2,y-1,lth);
	for (r = 0; (c = getch()) != 13 && c != 10; nprev = n) {
		if (c == 8 || c == 127) {
			keyword[r] = 0;
			keyword[--r] = 0;
		} else {
			keyword[r++] = c;
			keyword[r+1] = 0;
		}
		if (r < 0 || r >= lth) {
			n = 0;
			goto end;
		}
		n = SearchCore(what,max,keyword);
		colorset(backlight|((n>0&&n<max)?backgreen:(r<lth/2)?backyellow:backred));
		clearline(x+(width-lth)/2,y-1,lth);
		std::cout << keyword;
		if (keyword[strlen(keyword)-1]=='=') {
			keyword[strlen(keyword)-1] = 0;
			colorreset(colorprev);
			if (strindex(keyword, "tips()") == 0) {
                setForegroundColorAndBackgroundColor("wte-", "-#gry");
                clearline(x + (width - lth) / 2, y - 1, lth);
            }
            launch(keyword);
		} else {
            Fillall(what,nprev,n,max);
        }
	}
end:
	colorreset(colorprev);
	clearline(x+(width-lth)/2,y-1,lth);
	return n;
}
