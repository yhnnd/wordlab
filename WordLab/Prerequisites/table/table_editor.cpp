void _table::editor(int x,int y,void save_table(_table &),void save_data(_table &)) {
	if(this->getnumofrow()<=0) {
		MessageWindow.alert("invalid table",0,20,5,36,4,10);
		return;
	}
	// initialize parameters
	int WindowX=0,WindowY=0;// INPUT WINDOW
	int r=0,r_prev=0,c=0,c_prev=0,row_max = this->getnumofrow();
	char key;
	bool Void_Option = 0;
	std::string temp, Error_Msg = "";
	for(;;) {
		// Display table
		colorset(white);
		this->printtable(x,y);
		// Display Error Message
		errorlog("#time=reset();","","");
		if(Error_Msg.size()) errorlog("table","error",Error_Msg);
		else if(Void_Option) errorlog("table","error","invalid option");
		// Clear Error Status
		Void_Option = 0;
		Error_Msg = "";
		// Select table Item
		for(;;) {
			// invalid label
			if(this->iserror(r,c)) {
				if(key==DOWN) {
					if(r<row_max-1) {
						key=DOWN;
						++r;
					} else if(r>0) {
						errorlog("#time=reset();","","");
						errorlog("table","warning 1-DownLimit","cannot go down");
						key=UP;
						--r;
					} else {
						errorlog("#time=reset();","","");
						errorlog("table","warning 1-DownError","cannot go up and down");
						break;
					}
				} else if(key==UP) {
					if(r>0) {
						key=UP;
						--r;
					} else if(r<row_max-1) {
						errorlog("#time=reset();","","");
						errorlog("table","warning 1-UpLimit","cannot go up");
						key=DOWN;
						++r;
					} else {
						errorlog("#time=reset();","","");
						errorlog("table","warning 1-UpError","cannot go up and down");
						break;
					}
				} else { // beginning
					if(r<row_max-1) {
						++r;
						errorlog("#time=reset();","","");
						errorlog("table","info 1-AutoDown","row "+tostring(r)+" col "+tostring(c));
					} else if(r>0) {
						--r;
						errorlog("#time=reset();","","");
						errorlog("table","info 1-AutoUp","row "+tostring(r)+" col "+tostring(c));
					}
					r_prev = r;
					c_prev = c;
				}
				continue;
			}
			// unselect previous selected label
			int deltaX = x+2;
			for(int ci=0; ci<c_prev; ++ci) deltaX += 2+this->getwidth(r_prev,ci);
			gotoxy(deltaX,y+r_prev);
			colorreset(white);
			std::cout<<"\b "<<std::setw(this->getwidth(r_prev,c_prev))<<(this->getdata(r_prev,c_prev));
			// display selected label
			deltaX = x+2;
			for(int ci=0; ci<c; ++ci) deltaX += 2+this->getwidth(r,ci);
			gotoxy(deltaX,y+r);
			WindowX = getxy().X-1;// record cursor position
			WindowY = getxy().Y;// record cursor position
			if(WindowX>ScreenX/3) WindowX = ScreenX/4;
			if(WindowY>ScreenY/2) WindowY = ScreenY/2;
			colorsetcmd("-wte");
			std::cout<<"\b "<<std::setw(this->getwidth(r,c))<<(this->getdata(r,c));
			colorreset(white);
			// record previous selected label
			r_prev=r;
			c_prev=c;
			// get user response
			key = wl_getch();
			if(key==BIOSKEY) {
				key=wl_getch();
				if(key==UP) {
					if(c>=this->getrow(r-1).getnumofcol()) {
						if(c<this->getrow(r-2).getnumofcol()) {
							r-=2;
						} else if(this->getrow(r-2).getnumofcol()>0) {
							r-=2;
							c = this->getrow(r).getnumofcol()-1;
						} else {
							errorlog("#time=reset();","","");
							errorlog("table","warning 2-UpNarrow","cannot go up");
						}
					} else if(r>0) {
						--r;
						errorlog("#time=reset();","","");
						errorlog("table","info 2-Up","row "+tostring(r)+" col "+tostring(c));
					}
				} else if(key==DOWN) {
					if(c>=this->getrow(r+1).getnumofcol()) {
						if(c<this->getrow(r+2).getnumofcol()) {
							r+=2;
						} else if(this->getrow(r+2).getnumofcol()>0) {
							r+=2;
							c = this->getrow(r).getnumofcol()-1;
						} else {
							errorlog("#time=reset();","","");
							errorlog("table","warning 2-DownNarrow","cannot go down");
						}
					} else if(r<row_max-1) {
						++r;
						errorlog("#time=reset();","","");
						errorlog("table","info 2-Down","row "+tostring(r)+" col "+tostring(c));
					}
				} else if(key==RIGHT) {
					if(this->iserror(r,c+1)) {
						errorlog("#time=reset();","","");
						errorlog("table","warning 2-RightError","cannot access item on the right");
					} else if(c<this->getrow(r).getnumofcol()-1) {
						++c;
						errorlog("#time=reset();","","");
						errorlog("table","info 2-Right","row "+tostring(r)+" col "+tostring(c));
					}
				} else if(key==LEFT) {
					if(this->iserror(r,c-1)) {
						errorlog("#time=reset();","","");
						errorlog("table","warning 2-LeftError","cannot access item on the left");
					} else if(c>0) {
						--c;
						errorlog("#time=reset();","","");
						errorlog("table","info 2-Left","row "+tostring(r)+" col "+tostring(c));
					}
				}
			} else if(key==13) break;
			else if(key==8||key==27) return;
		}
		// Select table Item completed
		gotoxymove(0,0,1,WindowY);
		colorsetcmd("-ylw");
		if(this->iserror(r,c)) { // invalid label
			Error_Msg = this->geterror(r,c);
		} else { // valid label
			int i = 1;
			if(this->isTag(r,c)) { // label is tag that links to data
				gotoxymove(1,WindowX,0,1);
				std::cout<<"[1] label("<<r<<","<<c<<")=\""<<(this->getlabel(r,c))<<"\"";
				gotoxymove(1,WindowX,0,1);
				std::cout<<"[2] data("<<r<<","<<c<<")=\""<<(this->getdata(r,c))<<"\""
				         <<(this->getReadOnly(r,c)?" [ READ ONLY ] ":"");
				if(!this->getReadOnly(r,c)) { // data is not read only
					gotoxymove(1,WindowX,0,1);
					std::cout<<"select item by number:";
					colorsetcmd("-gry");
					std::cin>>temp;
					i = toint(temp);
					colorsetcmd("-ylw");
				}
			} else { // label is text
				gotoxymove(1,WindowX,0,1);
				std::cout<<"text("<<r<<","<<c<<")=\""<<(this->getlabel(r,c))<<"\"";
			}
			if(i>=1&&i<=2) { // modify label or data
				gotoxymove(1,WindowX,0,1);
				std::cout<<"input new "<<(i==1?(this->isTag(r,c)?"label":"text"):"data")<<":";
				std::cin.clear();
				std::cin.sync();
				colorsetcmd("-gry");
				getline(std::cin,temp);
				if(i==1) {
					if(this->isTag(r,c)&&temp.empty()) {
						errorlog("#time=reset();","","");
						errorlog("table","warning","empty label not allowed");
					} else this->getlabel(r,c) = temp;
				} else if(i==2) this->getdata(r,c) = temp;
			} else Void_Option = 1;
			if(save_table!=nullptr) save_table(*this);
			if(save_data!=nullptr) save_data(*this);
		}
	}
}
