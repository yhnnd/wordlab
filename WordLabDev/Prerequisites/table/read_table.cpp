void _table::readtable( std::istream & is ) {
	std::string s;
	while(getline(is,s)) {
		if(s[0]=='+') {
			_tablerow rowTemp;
			rowTemp.setcol(0,s);
			rows.push_back(rowTemp);// set row border
		} else {
			int num_column=-1;
			std::stringstream ss(s),ss2(s);
			std::string temp,temp2;
			// read num of column
			while(ss>>temp) if(*(temp.end()-1)=='|') ++num_column;
			// read column width
			std::vector<int> colwidth(num_column);
			for(int i=0,j=-1; i<s.end()-s.begin(); ++i) {
				if(s[i]=='|') colwidth[++j]=-1;
				else ++colwidth[j];
			}
			// set each column
			setrow(num_column);
			num_column=-1;
			while(ss2>>temp) {
				if(*(temp.end()-1)=='|') {
					if(temp[0]!='|') temp2+=(temp2.length()?" ":"")+temp.substr(0,temp.find('|'));
					// set column
					if(++num_column) setcol(colwidth[num_column-1],getlabel(temp2));
					temp2="";
				} else temp2+=(temp2.length()?" ":"")+temp;
			}
		}
	}
	setcolborder('|');
}
void _table::readtable( std::string const & filename) {
	std::ifstream fin(filename.c_str());
	readtable(fin);
	fin.close();
}
