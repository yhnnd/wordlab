void dialog::output(const string msg,bool Times,WORD color,string title,int x,int y,bool enableBSV) {
	static bool already_reseted = false;
	bool reset = false;
	if ( title.empty() ) title = "system";
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
	colorset(white);
	for( int ln = 1; ln <= 3; ln++ ) {
		clearline(x+5,y+1+ln*(1+SayStyle),60);
		if( ln==3 and not Times ) bar(msg.length(),LINEMAX);
		colorset( ln == 3 ? lightyellow : yellow );
		cout<<title<<": ";
		colorset( ln == 3 ? color : green );
		switch(ln) {
			case 1:
				if(enableBSV) bsvline(memoryout[2].c_str());
				else cout<<memoryout[2];
				break;
			case 2:
				if(enableBSV) bsvline(memoryout[1].c_str());
				else cout<<memoryout[1];
				break;
			case 3:
				if(enableBSV) bsvline(msg.c_str());
				else cout<<memoryout[0];
				break;
			default:
				break;
		}
	}
	if ( reset == false ) {
		memoryout[2] = memoryout[1];
		memoryout[1] = memoryout[0];
	}
}
