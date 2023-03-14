std::string dialog::input(std::string name,bool display,int linemax,int x,int y) {
	if(name.empty()) name = "Unknown";
	colorset(white);
	for(int ln = 1; ln <= 3; ln++ ) {
		clearline(x+5,(SayStyle)?y+2+2*ln:y+10-ln,60);
		colorset(ln==3?(light|blue):blue);
		cout<<name<<": ";
		colorset(gray);
		if(ln==1) cout<<memoryin[2];
		else if(ln==2) cout<<memoryin[1];
	}
	colorreset(white);
	// input
	char line[linemax];
	this -> InputResult = listen(line,0,display,{13,0,EOF},linemax);
	if( strlen(line) == 0 && this -> InputResult == 0 ){
		this -> settings(x,y);
		return input(name,display,linemax,x,y);
	}
	memoryin[0] = line;
	memoryin[2] = memoryin[1];
	memoryin[1] = display ? memoryin[0] : string(strlen(line),'*');
	return memoryin[0];
}
