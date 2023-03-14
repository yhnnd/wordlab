int scriptprocessor::selectshow(const std::string & prev,const std::string & curr,const int dir,const int width,const int interval,const WORD color) {
	int l1 = prev.length(), l2 = curr.length();
	std::string s;
	recordxy(ogpos);
	colorrecord(ogcolor);
	colorset(color);
	if(dir>0) {
		s = prev + curr;
		for(int i = 0; i <= l1; i++ ) {
			gotoxy(ogpos);
			clearline(width);
			for(int j = 0; j < l2; j++ ) printf("%c",s[j+i]);
			Sleep(interval);
		}
	} else if(dir<0) {
		s = curr + prev;
		for(int i = l1; i >= 0; i-- ) {
			gotoxy(ogpos);
			clearline(width);
			for(int j = 0; j < l2; j++ ) printf("%c",s[j+i]);
			Sleep(interval);
		}
	} else {
		gotoxy(ogpos);
		clearline(width);
		printf("%s",curr.c_str());
	}
	colorreset(ogcolor);
    return 0;
}
int scriptprocessor::select(const std::string & line) {
	recordxy(ogpos);
	std::string name = getname(line);
	std::string value = getparam(line);
	if(value[0]=='\"') removebrackets(value,"\"","\"");
	std::string filename = value;
	int i = 0, iprev = 0, max = filelines(filename,1);
	if(max<=0) {
		printf("select: fopen(%s) is null\n",filename.c_str());
		if(_debug) wl_getch();
		return 0;
	}
	std::string s[max], optionName[max], optionValue[max];
	std::ifstream fin(filename);
	for( int i = 0; std::getline(fin,s[i]); ++i ) ;
	fin.close();
	for( i = 0; i < max; i++ ) {
		optionName[i] = getname(s[i]);
		optionValue[i] = getvalue(s[i]);
	}
	for(iprev = 0, i = 0; i < max; limit(i,i,0,max-1)) {
		gotoxy(ogpos);
		selectshow(optionName[iprev],optionName[i],i-iprev,32,10,blue|backwhite);
		iprev = i;
		char k = wl_getch();
		if( k == 13 ) break;
		else if( k == 8 ) {
			i = -1;
			break;
		} else if(k=='s'||k=='d') i++;
		else if(k=='w'||k=='a') i--;
	}
	if(i>=0&&i<max) dataset.set(name,optionValue[i]);
	return 0;
}
