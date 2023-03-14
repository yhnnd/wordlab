int messageblock::Search(char what[][LINEMAX],int N) {
	int r, n = 0, nprev = N, lth = 30;
	char c,keyword[lth];
	strclr(keyword);
	colorrecord(colorprev);
	colorset(bothwhite);
	clearline(x+(width-lth)/2,y-1,lth);
	for(r=0; (c=wl_getch())!=13; nprev=n) {
		if(c==8) {
			keyword[r]=0;
			keyword[--r]=0;
		} else {
			keyword[r++]=c;
			keyword[r+1]=0;
		}
		if(r<0||r>=lth) {
			n=0;
			goto end;
		}
		n = SearchCore(what,max,keyword);
		colorset(backlight|((n>0&&n<max)?backgreen:(r<lth/2)?backyellow:backred));
		clearline(x+(width-lth)/2,y-1,lth);
		std::cout<<keyword;
		if(keyword[strlen(keyword)-1]=='=') {
			keyword[strlen(keyword)-1]=0;
			colorreset(colorprev);
			if(host::name.length()&&strindex(keyword,"tips")==0) {
				colorset(white|backlight);
				clearline(x+(width-lth)/2,y-1,lth);
				system((host::name+" tips ").c_str());
			} else if(host::name.length()&&system((host::name+" launch "+keyword).c_str())>=0);
			else std::cout<<maths::calc(keyword);
		} else Fillall(what,nprev,n,max);
	}
end:
	colorreset(colorprev);
	clearline(x+(width-lth)/2,y-1,lth);
	return n;
}
