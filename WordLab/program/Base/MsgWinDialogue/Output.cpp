void dialog::output(const string msg,bool Times,WORD color,string title,int x,int y,bool enableBSV) {
	static bool already_reseted = false;
	bool reset = false;
	if ( title.empty() ) {
        title = "system";
    }
	if ( msg.empty() ) {
		if ( already_reseted == false ) {
			memoryout[0] = memoryout[1];
			memoryout[1] = memoryout[2];
		}
		already_reseted = true;
		reset = true;
	} else {
		memoryout[0] = msg;
		already_reseted = false;
	}
//	setColor(lightwhite);
    setForegroundColorAndBackgroundColor("wte-", "-blk");
	for( int ln = 1; ln <= 3; ln++ ) {
		clearline(x+5,y+1+ln*(1+SayStyle),60);
		if( ln == 3 and not Times ) {
            bar(msg.length(),LINEMAX);
        }
//		setColor( ln == 3 ? lightyellow : yellow );
        if (ln == 3) {
            setForegroundColorAndBackgroundColor("ylw-", "-blk");
        } else {
            setForegroundColorAndBackgroundColor("#ylw-", "-blk");
        }
		cout<<title<<": ";
//		setColor( ln == 3 ? color : green );
        if (ln == 3) {
            std::string get_mac_os_foreground_color_code(WORD color);
            setForegroundColorAndBackgroundColor(get_mac_os_foreground_color_code(color), "-blk");
        } else {
            setForegroundColorAndBackgroundColor("grn-", "-blk");
        }
        const int i = 3 - ln;
//        printf("\ndialog::output title = %s, memeoryout[i] = %s, Times = %d, ln = %d, i = %d\n", title.c_str(), memoryout[i].c_str(), Times, ln, i);
        if (memoryout[i].length()) {
            if (enableBSV) {
                bsvLine(memoryout[i].c_str());
            } else {
                cout << memoryout[i];
            }
        }
	}
//    printf("\ndialog::output done\n");
	if ( reset == false ) {
		memoryout[2] = memoryout[1];
		memoryout[1] = memoryout[0];
	}
}
