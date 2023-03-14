class crossword{
	int max,x,y,zx,zy,w,h,wboard,hboard;
	bool available,*solved;
	string foldername;
	board Board;
	crossword_word *Word;
	public:
	crossword(const string foldername,const bool LoadPrev,int x,int y,int z,int w,int h){
		this->Word=nullptr;
		this->solved=nullptr;
		this->foldername=foldername;
		this->x=x;
		this->y=y;
		this->zx=this->zy=z;
		this->wboard=this->w=w;
		this->hboard=this->h=h;
		this->Board.set(wboard,hboard,x,y);
		if(LoadPrev) this->loadboardfrom(foldername);
		//count words in file
		ifstream in(foldername+"\\words.dat");
		string line="";
		this->max=0;
		if(in.is_open()){
			while(getline(in,line)){
				if(line.find("n=")==0) this->max++;
				else break;
			}
		}else goto ErrorOpeningFolder;
		in.close();
		if(this->max<=0){
			ErrorOpeningFolder:
			errorlog("crossword()","error opening folder",foldername);
			this->w=this->h=this->available=0;
		}else{
			//allocate memory
			this->Word=new crossword_word[max];
			this->solved=(bool*)malloc(sizeof(bool[max]));
			//initialize words
			for(int i=0;i<max;i++){
				this->Word[i]=this->Board;
				this->solved[i]=0;
			}
			//read words from file
			if(this->loadwordfrom(foldername)){
				this->available=1;
				for(int i=0;i<max;i++) this->check(i,"");
			}else{
				errorlog("crossword","error opening folder",foldername);
				this->max=this->available=0;
			}
		}
	}
	~crossword(){
		delete[] Word;
		free(solved);
	}
	bool Available(){
		return this->available;
	}
	int setword(int n,int x,int y,int z,int xd,int yd,
	string word,string type,string def,string defreverse=""){
		int r=0,lth=word.length();
		if(word.empty()){
			return errorlog("words.setword","cannot set empty word",tostring(n));
		}else if(!Word[n].writable()){
			string msg="cannot rewrite ";
			msg+=Word[n].getword();
			msg+="(";
			msg+=tostring(n);
			msg+=") with";
			return errorlog("words.setword",msg,word);
		}
		for(r=0;r<lth;r++) if(this->Board.writable(x+xd*r,y+yd*r,word[r])==0) break;
		if(r==lth){
			for(r=0;r<lth;r++){
				this->Board.setwritable(x+xd*r,y+yd*r,0);
				this->Board.setletter(x+xd*r,y+yd*r,word[r]);
			}
			if(n<max) return Word[n].set(x,y,zx,zy,xd,yd,word,type,def,defreverse);
			else return errorlog("words.setword has no space for",word,tostring(n));
		}else return errorlog("words.setword board not available for",word,tostring(r));
	}
	int check(int n,string s){
		return this->solved[n]=this->Word[n].check(s);
	}
	int check(initializer_list<string> vals){
		auto begin=vals.begin(),end=vals.end();
		for(auto p=begin;p!=end&&p-begin<max;++p){
			this->check(p-begin,*p);
		}
	}
	int SelectWord(){
		if(this->available==0) return -1;
		int i=-1,key=0;
		bool available=0;
		goto ceil;
		for(;;roll(i,i,0,max-1)){
			this->show();//refresh board
			this->Word[i].selected();
			key=getch();
			process:
			if(key==13) break;
			else if(key>='0'&&key<='9') i=key-'0';
			else if(strchr("awe",key)){
				floor:
				for(i--;i>=0;i--){
					if(this->Word[i].accord(Board.getrotate())) break;
				}
			}else if(strchr("sd",key)){
				ceil:
				for(i++;i<max;i++){
					if(this->Word[i].accord(Board.getrotate())) break;
				}
			}else return -1;
			if(i>=0&&i<max) available=1;
			else if(!available) break;
			else if(i>=max){i=-1;goto ceil;}
			else if(i<0){i=max;goto floor;}
		}
		return i;
	}
	int AnswerWord(int n){
		if(!(n>=0&&n<max)) return 0;
		string s;
		cin>>s;
		return this->check(n,s);
	}
	int hint(int n){
	}
	int rotate(int t){
		Board.setrotate(Board.getrotate()+t);
		swap(this->w,this->h);
		int l=::max(this->w,this->h);
		clearscreen(this->x,this->y,2*zx*l,zy*l+1);
	}
	void info(const char key){
		int l=::max(this->w,this->h);
		clearline(x,y+zy*l,ScreenX-x);
		cout<<"total:"<<max;
		int i=0,r=0;
		for(i=0,r=0;r<max;r++) i+=solved[r];
		cout<<" solved:"<<i;
		if(key){
			cout<<" command:";
			if(isalnum(key)) cout<<key;
			else cout<<"invalid";
		}
		int m=::max(w,h)+1,xt=x+2*zx*m+1,yt=y+zy*m/2;
		clearscreen(xt-1,yt-1,5,3);
		gotoxy(xt,yt);
		cout<<"top";
		switch(this->Board.getrotate()%4){
			case 0:gotoxy(xt+1,yt-1);break;
			case 1:gotoxy(xt+3,yt);break;
			case 2:gotoxy(xt+1,yt+1);break;
			case 3:gotoxy(xt-1,yt);break;
			default:break;
		}
		cout<<"*";
	}
	int show(){
		if(!available) errorlog("crossword.show()","cannot open",foldername);
		colorrecord(colorprev);
		int r=0,i=0;
		for(r=0;r<w;r++){
			gotoxy(x+2*zx*r,y-1);
			cout<<setfill(' ')<<setw(2*zx)<<right<<r;
		}
		for(r=0;r<h;r++){
			gotoxy(x-2*zx,y+zy*r);
			cout<<setw(2*zx)<<right<<r;
		}
		//show board
		for(r=0;r<wboard;r++){
			for(i=0;i<hboard;i++){
				Board.show({r,i,this->zx,this->zy});
			}
		}
		//show words
		for(r=0;r<max;r++) Word[r].show();
		colorreset(colorprev);
		return available;
	}
	int settings(){
	}
	int savewordto(string filename,string time){
		ofstream os(filename);
		if(os.is_open()){
			for(int r=0;r<max;r++){
				tuple<ofstream&,int> info={os,r};
				Word[r]>>info;
			}
		}
		os<<time<<endl;
		os.close();
	}
	int saveviewto(string filename,string time){
		ofstream os(filename);
		if(os.is_open()){
			os<<setw(4)<<"";
			for(int x=0;x<wboard;x++) os<<setw(2)<<right<<x;
			os<<endl;
			for(int y=0;y<hboard;y++){
				os<<setw(4)<<right<<y;
				for(int x=0;x<wboard;x++){
					auto c=Board.getletter(x,y);
					os<<" "<<(isalpha(c)?c:' ');
				}
				os<<endl;
			}
		}
		os<<time<<endl;
		os.close();
	}
	int saveboardto(string filename,string time){
		ofstream os(filename);
		if(os.is_open()){
			for(int y=0;y<hboard;y++){
				for(int x=0;x<wboard;x++){
					char c=Board.getletter(x,y);
					os<<(c==' '?'*':c);
					os<<" "<<Board.getwritable(x,y);
					os<<" "<<Board.getvisible(x,y);
					os<<" "<<Board.getcolor(x,y);
					os<<" ";
				}
				os<<endl;
			}
		}
		os<<time<<endl;
		os.close();
	}
	int save(){
		time_t t=time(NULL);
		string time=asctime(localtime(&t));
		savewordto(foldername+"\\words.dat",time);
		saveviewto(foldername+"\\view.dat",time);
		saveboardto(foldername+"\\board.dat",time);
		status("game saved");
	}
	int loadwordfrom(string foldername){
		ifstream fin(foldername+"\\words.dat");
		if(fin.is_open()){
			int i=0;
			for(i=0;i<max&&!fin.eof();i++){
				tuple<ifstream&,int> info(fin,i);
				Word[i]<<info;
				Word[i].setz(this->zx,this->zy);
			}
			fin.close();
			return i;
		}
		else return 0;
	}
	int loadboardfrom(string foldername){
		ifstream fin(foldername+"\\board.dat");
		if(fin.is_open()){
			char c=' ';
			int n=0;
			for(int y=0;y<h;y++){
				for(int x=0;x<w;x++){
					if(fin.eof()) break;
					if(fin>>c) Board.setletter(x,y,c);
					if(fin>>n) Board.setwritable(x,y,isalpha(c)?0:n);
					if(fin>>n) Board.setvisible(x,y,n);
					if(fin>>n) Board.setcolor(x,y,n);
				}
			}
		}
		fin.close();
	}
};
