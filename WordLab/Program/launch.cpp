// updated on 2017.03.09
//如果 launch 返回負值, 则调用 launch 的 MessageWindow 计算 msg 的值
// all function names are of lower characters
// return value is number of function order
//  0 function List() or Translate()
// -1 unknown function name (default)
// -2 cannot open function name file
int launch(string msg) {
	vector<string> FunctionName;
	FunctionName.push_back("list()");
	//read function names
	ifstream fin(LaunchFunctionNamesFilename);
	if(fin.is_open()) {
		string line;
		while(!fin.eof()) {
			if(getline(fin,line)&&line.size()) FunctionName.push_back(line);
		}
		fin.close();
	} else {
		errorlog("launch","cannot open",LaunchFunctionNamesFilename);
		return -2;
	}
	if(msg==FunctionName[0]) { //print a list of all function names
		_table t;
		t.setrowborder(83).setrow("a list of functions that LAUNCH supports").setrowborder();
		t.setrow(4).setcol(3,"No.").setcol(35,"function").setcol(3,"No.").setcol(35,"function").setrowborder();
		for(int i=0,HalfSize=(FunctionName.size()+1)/2; i<HalfSize; ++i) {
			t.setrow(4).setcol(tostring(i)).setcol(FunctionName[i]);
			if(i+HalfSize<FunctionName.size())
				t.setcol(tostring(i+HalfSize)).setcol(FunctionName[i+HalfSize]);
			else t.setcol("").setcol("");
		}
		t.setrowborder().setcolborder('|').editor();
		t.clear();
		return 0;
	} else if(msg==FunctionName[1]) {
		csvqueryshell();
		return 1;
	} else if(msg==FunctionName[2]) {
		cout<<Volume(lang::EN,1,30,"");
		return 2;
	} else if(msg.find(FunctionName[3])==0) {
		Load.UpdateCheck(msg);
		return 3;
	} else if(msg.find(FunctionName[4])==0) {
		Load.Update();
		return 4;
	} else if(msg==FunctionName[5]) {
		cout<<DatabaseVersion();
		return 5;
	} else if(msg==FunctionName[6]) {
		cout<<SoftwareVersion();
		return 6;
	} else if(msg==FunctionName[7]) {
		clearCache();
		cout<<"done";
		return 7;
	} else if(msg==FunctionName[8]) {
		auto words=[] {
			char s[64];
			cout<<"enter:";
			listen(s,0,1,{EOF,0,13},64);
			string s2(s);
			return s2;
		};
		AddNew(words());
		return 8;
	} else if(msg==FunctionName[9]) {
		WordInsert();
		return 9;
	} else if(msg==FunctionName[10]) {
		auto words=[] {
			char s[64];
			cout<<"enter:";
			listen(s,0,1,{EOF,0,13},64);
			string s2(s);
			return s2;
		};
		AddPhrase(words());
		return 10;
	} else if(msg==FunctionName[11]) {
		scriptshell(false);
		return 11;
	} else if(msg.find(FunctionName[12])==0) {
		string param[4];
		string::size_type i=0,j=0,r=0;
		i=msg.find("(")+1;
		for(r=0; r<4; r++) {
			if((j=msg.find_first_of(",)",i))==string::npos) break;
			param[r].assign(msg,i,j-i);
			i=j+1;
		}
		if(r<4) cout<<"[Error] 4 parameters required: begin, end, admin, pwd";
		else if(sortlib(stoi(param[0]),stoi(param[1]),param[2],param[3])==0) cout<<"done";
		else cout<<"error";
		return 12;
	} else if(msg==FunctionName[13]) {
		CrosswordFramework();
		return 13;
	} else if(msg==FunctionName[14]) {
		cout<<Load.lastlaunch();
		return 14;
	} else if(msg==FunctionName[15]) {
		char keyword[LINEMAX];
		popup("Search Compact",0);
		index(keyword,10,9);
		return 15;
	} else if(msg==FunctionName[16]) {
		WLFramework();
		return 16;
	} else if(msg==FunctionName[17]) {
		sts STS;
		STS.Framework();
		return 17;
	} else if(msg==FunctionName[18]) {
		sts STS;
		STS.FrameworkDebug();
		return 18;
	} else if(msg==FunctionName[19]) {
		Load.Engines();
		return 19;
	} else if(msg==FunctionName[20]) {
		Load.Values();
		return 20;
	} else if(msg==FunctionName[21]) {
		Load.System();
		return 21;
	} else if(msg==FunctionName[22]) {
		Load.History();
		return 22;
	} else if(msg==FunctionName[23]) {
		User.login();
		return 23;
	} else if(msg==FunctionName[24]) {
		cout<<"assistant not installed";
		return 24;
	} else if(msg==FunctionName[25]) {
		Help();
		return 25;
	} else if(msg==FunctionName[26]) {
		setversion();
		return 26;
	} else if(msg==FunctionName[27]) {
		WordSortCheck();
		return 27;
	} else if(msg==FunctionName[28]) {
		SearchReverse();
		return 28;
	} else if(msg==FunctionName[29]) {
		SearchSimilarShell();
		return 29;
	} else if(msg==FunctionName[30]) {
		practices();
		return 30;
	} else if(msg.find(FunctionName[31])==0) {
		if(msg.find(",")==string::npos||msg.find(")")==string::npos) {
			errorlog("similar","error","parameter unrecognizable");
		} else {
			string word=msg.substr(msg.find("(")+1,msg.find(",")-msg.find("(")-1);
			int amount=toint(msg.substr(msg.find(",")+1,msg.find(")")-msg.find(",")-1));
			WLSearchSimilarSpelling(word,amount);
		}
		return 31;
	} else { //translate msg as a word
		int i = 0, lth = msg.length();
		if((i=Search(msg.c_str(),lth))>0) {
			cout<<"{"
			<<"\"db-"<<lth<<"-"<<i<<'\"'
			<<','
			<<'\"'<<sortofword(msg.c_str())<<'\"'
			<<','
			<<'\"'<<Chinese(lth,i)<<'\"'
			<<"}";
			return 0;
		}
	}
	errorlog("launch","unknown function name",msg);
	return -1;
}
