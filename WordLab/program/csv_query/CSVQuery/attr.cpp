	class {
		public:
		string name;
		bool req;
		class{
			public:
			string self;
			string from;
			string to;
			int clear(){
				self.clear();
				from.clear();
				to.clear();
                return 0;
			}
			string surround(int which,string br1,string br2){
				string& p=(which==0)?self:((which==1)?from:to);
				p=br1+p+br2;
				return p;
			}
		}value;
		int toString(int n) {
			if (n < 0) {
                return n;
            }
			gotoxy(1, getxy().Y);
			recordColor(colorPrev, "toString");
			setColor(backlightwhite, "toString");
			cout<<"attr["<<n<<"]=";
			cout<<"{name:"<<this->name<<",";
			cout<<"req:"<<req<<",";
			cout<<"self:"<<this->value.self<<",";
			cout<<"from:"<<this->value.from<<",";
			cout<<"to:"<<this->value.to<<"}"<<endl;
			resetColor(colorPrev, "toString");
			return n;
		}
		int clear(){
			name.clear();
			value.clear();
			req = 1;
            return 0;
		}
	}attr[6];
