// updated on 2017.03.09
// updated on 2023.04.29

void launchTips(char *msg, const std::vector<std::string> functionNames, const sts::consoleColor colorStart, const sts::consoleColor colorEnd) {

    const std::string suggestions = join(functionNames, ",") + ";";

    recordColor(colorprev, "launchTips");

    const auto pos = getxy();

    setForegroundColorAndBackgroundColor(colorStart.foregroundColor, colorStart.backgroundColor);
    inputCore(msg, 0, true, {13, 10, KEY_ESC, '='}, suggestions.c_str(), true, pos);

    gotoxy(pos);
    setForegroundColorAndBackgroundColor(colorEnd.foregroundColor, colorEnd.backgroundColor);
    printf("%s=", msg);

    resetColor(colorprev, "launchTips");
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
			if (getline(fin,line)&&line.size()) {
                functionNames.push_back(line);
            }
		}
		fin.close();
	} else {
        errorLog("launch", "cannot open", LaunchFunctionNamesFilename);
		return -2;
	}

	if (msg == functionNames[0]) {
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
	} else if (msg == functionNames[10]) {
		const auto words = [] {
			char s[64];
			cout << "enter:";
			listen(s, 0, 1, {EOF, 0, 13}, 64);
			string s2(s);
			return s2;
		};
        addPhrase(words(), AddMode::AddPhrase);
		return 10;
	} else if(msg == functionNames[11]) {
		scriptshell(false);
		return 11;
	} else if(msg.find(functionNames[12]) == 0) {
		vector<string> params;
		string::size_type i = 0, j = 0, r = 0;
		i = msg.find("(") + 1;
		for(r = 0; r < 2; r++) {
			if ((j = msg.find_first_of(",)", i)) == string::npos) {
                break;
            }
			params.push_back(msg.substr(i, j - i));
			i = j + 1;
		}
		if (params.size() != 2) {
            cout<<"[Error] 2 parameters required: begin, end";
        } else {
            params.push_back(DatabaseAdminName);
            params.push_back(DatabaseAdminPassword);
            if (sortlib(stoi(params[0]), stoi(params[1]), params[2], params[3]) == 0) {
                cout << "done";
            } else {
                cout << "error";
            }
        }
		return 12;
	} else if(msg == functionNames[13]) {
		CrosswordFramework();
		return 13;
	} else if(msg == functionNames[14]) {
		printf("\"%s\"", Load.lastLaunch().c_str());
		return 14;
	} else if(msg == functionNames[15]) {
		char keyword[LINEMAX];
		popup("Search Compact", 0);
		index(keyword, 10, 9, lightwhite, 0);
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
		setGUIVersion();
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
            errorLog("similar", "error", "parameter unrecognizable");
        } else {
            string word = msg.substr(msg.find("(") + 1, msg.find(",") - msg.find("(") - 1);
            int amount = toInt(msg.substr(msg.find(",") + 1, msg.find(")") - msg.find(",") - 1));
            WLSearchSimilarSpelling(word, amount);
        }
        return 31;
    } else if (msg == functionNames[32]) {
        char command[256];
        launchTips(command, functionNames, {"wte-", "-blk"}, {"wte-", "-#gry"});
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
    } else if (msg == functionNames[35]) {
        clearScreen();
        gotoxy(0, 1);
        printColorTable();
        return 35;
    } else if (msg == functionNames[36]) {
        clearScreen();
        gotoxy(0, 1);
        performanceTest();
        return 36;
    } else if (msg == functionNames[37]) {
        clearScreen();
        gotoxy(0, 1);
        colorLogs.printLogs();
        return 37;
    } else if (msg == functionNames[38]) {
        clearScreen();
        gotoxy(0, 1);
        molecular Molecular;
        Molecular.generateMolecularDatabase(_data_dir, "111111");
        printf("\nMolecular database generated. Press any key to continue.\n");
//        getch();
        return 38;
    } else if (msg.find(functionNames[39]) == 0) {
        const auto beginPos = msg.find("("), endPos = msg.find(")", beginPos + 1);
        if (beginPos == std::string::npos || endPos == std::string::npos) {
            printf("parameter required");
        } else {
            const std::string parameter = trim(msg.substr(beginPos + 1, endPos - beginPos - 1), "\"");
            if (parameter.empty()) {
                printf("parameter required");
            } else {
                molecular Molecular;
                Molecular.setWord(parameter.c_str());
                char definition[32];
                Molecular.getWordDefinitions(definition, sizeof(definition));
                printf("%-32s", (std::string("\"") + definition + "\"").c_str());
            }
        }
        return 39;
	} else { // translate msg as a word
		int i = 0, lth = msg.length();
		if ((i = Search(msg.c_str(), lth, false)) > 0) {
            const auto definitions = getWordDefinitions(lth, i);
			cout<<"{"
			<<"\"db-"<<lth<<"-"<<i<<'\"'
			<<','
			<<'\"'<< sortOfWord(msg.c_str()) <<'\"'
			<<','
			<<'\"' << (definitions.size() ? definitions[0].text : "") << '\"'
			<<"}";
			return 0;
		} else {
            bsvLine(maths::calculateWithBSVSupported(msg).c_str());
            return 0;
        }
	}
    errorLog("launch", "unknown function name", msg);
	return -1;
}
