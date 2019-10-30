class crossword_word{
	board *Board;
	int lth,x,y,zx,zy,xd,yd;
	string letter,type,def,defreverse;
	public:
	void setz(int zx,int zy){
		this->zx=zx;
		this->zy=zy;
	}
	crossword_word(){
		this->Board=nullptr;
		this->zx=this->zy=1;
		this->letter="";
		this->type="";
		this->def="";
		this->defreverse="";
	}
	crossword_word& operator=(board& Board){
		this->Board=&Board;
		return *this;
	}
	void operator>>(tuple<ofstream&,int> info){//save to file
		ofstream& os=get<0>(info);
		int n=get<1>(info);
		os<<"n="<<setw(2)<<left<<n;
		os<<" word="<<setw(16)<<((this->letter.empty())?"NULL":this->letter);
		os<<" lth="<<setw(2)<<this->lth;
		os<<" x="<<setw(2)<<this->x;
		os<<" y="<<setw(2)<<this->y;
		os<<" zx="<<setw(2)<<this->zx;
		os<<" zy="<<setw(2)<<this->zy;
		os<<" xd="<<setw(2)<<this->xd;
		os<<" yd="<<setw(2)<<this->yd;
		os<<" type="<<setw(8)<<((this->type.empty())?"NULL":this->type);
		os<<" def="<<setw(32)<<((this->def.empty())?"NULL":this->def);
		os<<" defr="<<setw(32)<<((this->defreverse.empty())?"NULL":this->defreverse);
		os<<endl;
	}
	void operator<<(tuple<ifstream&,int> info){//read from file
		ifstream& in=get<0>(info);
		int r,n=get<1>(info);
		int x,y,zx,zy,xd,yd;
		string word,type,def,defr;
		in.ignore(1024,'=');
		in>>r;
		if(r!=n){
			errorlog("word.readfromfile","error reading word",tostring(n));
			errorlog("detail","reading file word",tostring(r));
			return;
		}
		in.ignore(1024,'=');
		in>>word;
		in.ignore(1024,'=');
		in.ignore(1024,'=');
		in>>x;
		in.ignore(1024,'=');
		in>>y;
		in.ignore(1024,'=');
		in>>zx;
		in.ignore(1024,'=');
		in>>zy;
		in.ignore(1024,'=');
		in>>xd;
		in.ignore(1024,'=');
		in>>yd;
		in.ignore(1024,'=');
		in>>type;
		in.ignore(1024,'=');
		in>>def;
		in.ignore(1024,'=');
		in>>defreverse;
		in.ignore(1024,'\n');
		this->set(x,y,zx,zy,xd,yd,word,type,def,defr);
		if(this->Board==nullptr) errorlog("word.readfromfile","board not set");
		else{
			for(int i=0;i<word.length();i++){
				if(this->Board->getwritable(x+xd*i,y+yd*i))
				this->Board->setcolor(x+xd*i,y+yd*i,backwhite);
			}
		}
	}
	int set(int x,int y,int zx,int zy,int xd,int yd,
	string word,string type,string def,string defrev){
		this->x=(x>=0)?x:0;
		this->y=(y>=0)?y:0;
		this->zx=(zx>=1)?zx:1;
		this->zy=(zy>=1)?zy:1;
		this->xd=(xd>=-1&&xd<=1)?xd:0;
		this->yd=(yd>=-1&&yd<=1)?yd:0;
		this->letter=word;
		this->type=type;
		this->def=def;
		this->defreverse=defrev;
		this->lth=this->letter.length();
		if(this->defreverse.empty()) this->type="normal";
		else this->type="double-ended";
		return this->lth;
	}
	int check(const int r){
		int xt=x+xd*r,yt=y+yd*r;
		return (this->Board->getvisible(xt,yt))
		&&!(this->Board->getwritable(xt,yt))
		&&isalpha(this->Board->getletter(xt,yt))
		&&(this->Board->getcolor(xt,yt)==(backlight|backgreen));
	}
	int check(const int r,const char c){
		int xt=x+xd*r,yt=y+yd*r;
		if(c==letter[r]){
			this->Board->setvisible(xt,yt,1);
			this->Board->setletter(xt,yt,letter[r]);
			this->Board->setcolor(xt,yt,backlight|backgreen);
			return 1;
		}else{
			this->Board->setvisible(xt,yt,0);
			this->Board->setcolor(xt,yt,backlight|backred);
		}
		return 0;
	}
	int check(string s){
		int n_correct=0;
		if(this->Board==nullptr){
			errorlog("word.check","invalid board of ",s);
			return 0;
		}else if(s.empty()){
			for(int r=0;r<this->lth;r++){
				n_correct+=this->check(r);
			}
		}else{
			for(int r=0,slth=s.length();r<this->lth;r++){
				if(r<slth) n_correct+=this->check(r,s[r]);
				else this->check(r,' ');
			}
		}
		return n_correct==this->lth;
	}
	void show(int r){
		this->Board->show({x+xd*r,y+yd*r,zx,zy});
	}
	int show(){
		if(this->Board==nullptr) return errorlog("word.show","invalid board");
		colorrecord(colorprev);
		for(int r=0;r<lth;r++) this->show(r);
		colorreset(colorprev);
		return 0;
	}
	void selected(int r){
		WORD color=this->Board->getcolor(x+xd*r,y+yd*r);//record
		this->Board->setcolor(x+xd*r,y+yd*r,backyellow|backlight);//set
		this->Board->show({x+xd*r,y+yd*r,zx,zy});
		this->Board->setcolor(x+xd*r,y+yd*r,color);//reset
		int x=this->x,y=this->y;
		this->Board->getpos(&x,&y,zx,zy);
		gotoxy(x,y+zy);
		colorset(backlight|backcyan);
		cout<<this->def;
		colorreset(white);
	}
	int selected(){
		if(this->Board==nullptr) return errorlog("word.selected","invalid board");
		colorrecord(colorprev);
		for(int r=0;r<lth;r++) this->selected(r);
		colorreset(colorprev);
		return 0;
	}
	bool accord(int rotate_index){
		switch(rotate_index%4){
			case 0: return (xd>0);break;
			case 1: return (yd<0);break;
			case 2: return (xd<0);break;
			case 3: return (yd>0);break;
			default:return 0;break;
		}
		return 0;
	}
	bool writable(){
		return letter.empty();
	}
	string& getword(){
		return letter;
	}
	string& getdef(){
		return def;
	}
	string& getdefreverse(){
		return defreverse;
	}
};
