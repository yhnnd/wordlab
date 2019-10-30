int openlogwithpsf(window,std::string,int x0=0,int y0=0,int x=0,int y=0);
// open a window as a log file with log-processing-script-file
int openlogwithpsf(window win,std::string scriptfilename,int x0,int y0,int x,int y) {
	//load script file
	ifstream fscript(scriptfilename);
	if(!fscript.is_open()) return errorlog("window.OpenAsLog","cannot open script",scriptfilename);
	fscript.close();
	//init reader
	int key = 0;
	win.Reader(win.WINDOW_STATUS::active,x0,y0,1);
	for(;;) {
		x = strlen(win.text.line(y));
INPUT:
		int x0prev = x0, y0prev = y0;
		if(y0>y) y0 = y;//first line > focused line
		if(y0<=y-win.innerHeight()) y0 = y-win.innerHeight()+1;//first line <= focused line - height
		if(x0>x) x0 = x;//first char > focused char
		if(x0<=x-win.innerWidth()) x0 = x-win.innerWidth()+1;//first char <= focused char - width
		if(x0<0||x<win.innerWidth()) x0 = 0;//optimize first char
		if(y0<0) y0 = 0;
		if(x0!=x0prev||y0!=y0prev) win.Reader(win.WINDOW_STATUS::active,x0,y0,0);
		// lambda function printline
		auto printline = [](window win,int x0,int y0,int x,int y,bool seleted) {
			if( y-y0 < 0 or y-y0 >= win.innerHeight() ) return;
			// SET LINE COLOR
			if(seleted) {
				colorsetcmd(win.color[win.WINDOW_STATUS::active].error.content);//cmd
			} else {
				colorsetcmd(win.color[win.WINDOW_STATUS::active].text[y%2].content);//text
			}
			// PRINT LINE
			gotoxy(win.innerLeft(),win.innerTop()+(y-y0));
			for(int i = 0; i < win.innerWidth(); ++i) {
				if(x0+i<win.text.length(y))	cout<<win.text.line(y)[x0+i];
				else break;
			}
			// PRINT BACKGROUND
			cout<<setw(win.innerWidth()-(win.text.length(y)-x0))<<"";
		};
		printline(win,x0,y0,x,y-1,false);//above
		printline(win,x0,y0,x,y+1,false);//below
		printline(win,x0,y0,x,y,true);//current
		key = getch();
		if(key==-32) key = getch();//BIOSKEY
		if(key==KEY_ESC||key==KEY_DELETE) return 0;
		if(key==KEY_ENTER) {
			int i/*name NO.*/, pww = win.innerWidth()-1;// pop window width
			std::string value = "";
			std::vector<decltype(value)> name = {"word","defs"}, backcolors = {"-#ylw","-#grn"}, forecolors = {"-ylw","-grn"};
			gotoxy(win.innerLeft(),win.innerTop()+(y-y0)+(y-y0+1>=win.innerHeight()?-1:1));
			for(i = 0; i < name.size(); ++i) { //	Find Name And Value In Line (FNAV)
				PKC label = ("<"+name[i]+">").c_str();
				if(strncmp(label,win.text.line(y),strlen(label))==0) {
					value = string(win.text.line(y) + strlen(label));
					bsvline((string("<")+backcolors[i]+">(modify "+name[i]+" <"+forecolors[i]+">("+ value +")?").c_str(),
					        pww,"<",">","(",")","");
					break;
				}
			}//*(FNAV)
			if( i<name.size() and value!="" ) { // Name And Value Found (NAVF)
				char key = getch();
				if(key==-32) key = getch();//BIOSKEY
				if(key==KEY_ENTER) {
					PKC msg = "<-grn>( Search ) <-ylw>(  Add  ) <-red>( Delete ) <-cyn>( Update )";
					int n, nmax = 4, xborder = win.innerLeft()+2, yborder = win.innerTop()+1;
					while(n = MessageWindow.alert(msg,nmax,xborder,yborder,36,2,7)) {
						switch( n ) {
							case 1://Search
								if(name[i]=="word") {
									int winwidth = prerequisites::ScreenX - 6;//popup window width
									int lth = value.length();
									int LineNumber = Search(value.c_str(),lth);
									std::string defs = Translation(value,0);// 0 means get all defs
									defs = strfilter(defs,",","{");//filter bsv term tokens
									defs = strfilter(defs,";","}");//filter bsv term tokens
									auto result = string("<")+backcolors[i]+
									              ">(db-"+tostring(lth)+"-"+tostring(LineNumber)+
									              "<"+forecolors[i]+">( "+defs+" )";
									//popup db-location and defs of word
									popupcore(result,0,0,0,winwidth,false);
								}
								break;
							case 2://Add
								if(name[i]=="word") {
								} else if(name[i]=="defs") {
								}
								break;
							case 3://Delete
								if(name[i]=="word") {
								} else if(name[i]=="defs") {
								}
								break;
							case 4://Update
								if(name[i]=="word") {
								} else if(name[i]=="defs") {
								}
								break;
							default:
								goto MANIP_END;
								break;
						}
					}
MANIP_END:
					win.Reader(win.WINDOW_STATUS::active,x0,y0,0);
				}
			}//*NAVF
		} else if(key == UP) { //cursor up
			if(--y < 0) y = 0;//MINIMUM bound
			int lth = strlen(win.text.line(y));
			if(lth < x) x = lth;
			goto INPUT;
		} else if(key == DOWN) { //cursor down
			if(++y >= win.text.size()) y = win.text.size()-1;//MAXIMUM bound
			auto lth = strlen(win.text.line(y));
			if(lth < x) x = lth;
			goto INPUT;
		} else if(key == LEFT) { //cursor left
			if(--x < 0) {
				if(--y >= 0) x = strlen(win.text.line(y));
				else {
					y = 0;
					x = 0;
				}
			}
			goto INPUT;
		} else if(key == RIGHT) { //cursor right
			if(++x > strlen(win.text.line(y))) {
				if(++y < win.text.size()) x = 0;
				else {
					y = win.text.size()-1;
					--x;
				}
			}
			goto INPUT;
		}
	}
	colorreset(white);
	return win.text.size();
}
