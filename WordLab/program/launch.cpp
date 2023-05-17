// updated on 2017.03.09
// updated on 2023.04.29

void launchTips(char *msg, const sts::consoleColor colorStart, const sts::consoleColor colorEnd) {
    const char suggests[]=
            "query(),volume(),checkupdate(),update(),database(),software(),clearcache(),"
            "addnew(),addword(),addphrase(),script(),sortlib(),"
            "crossword(),lastlaunch(),searchcompact(),wordlinkage(),translater(),translaterpro(),"
            "settings.engines(),settings.values(),settings.system(),settings.history(),"
            "user.login(),list(),help(),settings.version(),"
            "wordsortcheck(),searchreverse(),searchsimilar(),"
            "practices(),similar(),tips(),wlscan(),checksafety();";

    colorrecord(colorprev);

    const auto pos = getxy();

    setForegroundColorAndBackgroundColor(colorStart.foregroundColor, colorStart.backgroundColor);
    inputcore(msg,0,true,{13,10,KEY_ESC,'='},suggests,true, pos);

    gotoxy(pos);
    setForegroundColorAndBackgroundColor(colorEnd.foregroundColor, colorEnd.backgroundColor);
    printf("%s=", msg);

    colorreset(colorprev);
}

int launchPrintList(vector<string> functionNames) {
    //print a list of all function names
    _table t;
    t.setrowborder(83).setrow("a list of functions that LAUNCH supports").setrowborder();
    t.setrow(4).setcol(3,"No.").setcol(35,"function").setcol(3,"No.").setcol(35,"function").setrowborder();
    for (int i = 0, HalfSize= (functionNames.size() + 1) / 2; i < HalfSize; ++i) {
        t.setrow(4).setcol(toString(i)).setcol(functionNames[i]);
        if(i+HalfSize < functionNames.size()) {
            t.setcol(toString(i+HalfSize)).setcol(functionNames[i + HalfSize]);
        } else {
            t.setcol("").setcol("");
        }
    }
    t.setrowborder().setcolborder('|').editor();
    t.clear();
    return 0;
}

// The return value of launch is: the value of msg(from MessageWindow) which was passed to launch.
// all function names are of lower characters
// return value is number of function order
//  0 function List() or Translate()
// -1 unknown function name (default)
// -2 cannot open function name file
int launch(const std::string msg) {
	vector<string> functionNames;
	functionNames.push_back("list()");
	//read function names
	ifstream fin(LaunchFunctionNamesFilename);
	if(fin.is_open()) {
		string line;
		while(!fin.eof()) {
			if(getline(fin,line)&&line.size()) functionNames.push_back(line);
		}
		fin.close();
	} else {
		errorlog("launch","cannot open",LaunchFunctionNamesFilename);
		return -2;
	}
	if(msg == functionNames[0]) {
        launchPrintList(functionNames);
		return 0;
	} else if(msg == functionNames[1]) {
		csvqueryshell();
		return 1;
	} else if(msg == functionNames[2]) {
		cout<<Volume(lang::EN,1,30,"");
		return 2;
	} else if(msg.find(functionNames[3]) == 0) {
		Load.UpdateCheck(msg);
		return 3;
	} else if(msg.find(functionNames[4]) == 0) {
		Load.Update();
		return 4;
	} else if(msg == functionNames[5]) {
		cout<<DatabaseVersion();
		return 5;
	} else if(msg == functionNames[6]) {
		cout<<SoftwareVersion();
		return 6;
	} else if(msg == functionNames[7]) {
		clearCache();
		cout<<"done";
		return 7;
	} else if(msg == functionNames[8]) {
		auto words=[] {
			char s[64];
			cout<<"enter:";
			listen(s,0,1,{EOF,0,13},64);
			string s2(s);
			return s2;
		};
		AddNew(words());
		return 8;
	} else if(msg == functionNames[9]) {
		addWordScript();
		return 9;
	} else if(msg == functionNames[10]) {
		auto words=[] {
			char s[64];
			cout<<"enter:";
			listen(s,0,1,{EOF,0,13},64);
			string s2(s);
			return s2;
		};
		AddPhrase(words());
		return 10;
	} else if(msg == functionNames[11]) {
		scriptshell(false);
		return 11;
	} else if(msg.find(functionNames[12]) == 0) {
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
	} else if(msg == functionNames[13]) {
		CrosswordFramework();
		return 13;
	} else if(msg == functionNames[14]) {
		cout<<Load.lastlaunch();
		return 14;
	} else if(msg == functionNames[15]) {
		char keyword[LINEMAX];
		popup("Search Compact",0);
		index(keyword, 10, 9, lightwhite);
		return 15;
	} else if(msg == functionNames[16]) {
		WLFramework();
		return 16;
	} else if(msg == functionNames[17]) {
		sts STS;
		STS.Framework();
		return 17;
	} else if(msg == functionNames[18]) {
		sts STS;
		STS.FrameworkDebug();
		return 18;
	} else if(msg == functionNames[19]) {
		Load.Engines();
		return 19;
	} else if(msg == functionNames[20]) {
		Load.Values();
		return 20;
	} else if(msg == functionNames[21]) {
		Load.System();
		return 21;
	} else if(msg == functionNames[22]) {
		Load.History();
		return 22;
	} else if(msg == functionNames[23]) {
		User.login();
		return 23;
	} else if(msg == functionNames[24]) {
        launchPrintList(functionNames);
		return 24;
	} else if(msg == functionNames[25]) {
		Help();
		return 25;
	} else if(msg == functionNames[26]) {
		setversion();
		return 26;
	} else if(msg == functionNames[27]) {
		WordSortCheck();
		return 27;
	} else if(msg == functionNames[28]) {
		SearchReverse();
		return 28;
	} else if(msg == functionNames[29]) {
		SearchSimilarShell();
		return 29;
	} else if(msg == functionNames[30]) {
		practices();
		return 30;
	} else if(msg.find(functionNames[31]) == 0) {
        if (msg.find(",") == string::npos || msg.find(")") == string::npos) {
            errorlog("similar", "error", "parameter unrecognizable");
        } else {
            string word = msg.substr(msg.find("(") + 1, msg.find(",") - msg.find("(") - 1);
            int amount = toInt(msg.substr(msg.find(",") + 1, msg.find(")") - msg.find(",") - 1));
            WLSearchSimilarSpelling(word, amount);
        }
        return 31;
    } else if (msg == functionNames[32]) {
        char command[256];
        launchTips(command, {"wte-", "-blk"}, {"wte-", "-#gry"});
        if (command[0]) {
            return launch(command);
        }
    } else if (msg == functionNames[33]) {
        if (AL) {
            WLscan();
        } else {
            popup("permission denied", 0);
        }
        return 33;
    } else if (msg == functionNames[34]) {
        db_is_secure(true, true);
        return 34;
	} else { //translate msg as a word
		int i = 0, lth = msg.length();
		if ((i = Search(msg.c_str(),lth)) > 0) {
			cout<<"{"
			<<"\"db-"<<lth<<"-"<<i<<'\"'
			<<','
			<<'\"'<< sortOfWord(msg.c_str()) <<'\"'
			<<','
			<<'\"'<<Chinese(lth,i)<<'\"'
			<<"}";
			return 0;
		} else {
            std::cout << maths::calc(msg);
            return 0;
        }
	}
	errorlog("launch","unknown function name",msg);
	return -1;
}
