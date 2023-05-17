int scriptshell(std::string filename,int print_debug_msg,int data_capacity,COORD pos,int w,int h) {
	std::string tempstr,logfolder;
	std::vector<std::string> lines, functname;
	lines.clear();
	if(filename=="new") { //new file
		std::string filename = host::datafolder+"temp.js";
		if (ScriptEditor(filename) == 0) {
            return 1;
        }
		std::ifstream fin(filename);
		// shouldn't be replaced with if(fin.bad())
		if(!fin.good()) errorlog("script shell","cannot open file",filename);
		std::string templine = "";
		bool firstword = true;
		while(fin>>tempstr) {// read file
			if (firstword == false) {
                templine += " ";
            }
			firstword = false;
			// merge multi-line scripts into single-line script
			templine += tempstr;
			auto pos = templine.find_last_of(";");
			if( pos!=std::string::npos ) {
				templine.erase(pos);
				lines.push_back(templine);
				templine.clear();
				firstword = true;
			}
		}
		fin.close();
	} else { //open file
		std::ifstream fin(filename);
		if(fin.is_open()) {
			while(std::getline(fin,tempstr)) lines.push_back(tempstr);
		} else {
			errorlog("script shell","cannot open file",tempstr);
			return 1;
		}
		fin.close();
	}
	// find all function names
	unsigned int n=0,l=strlen("function ");
	functname.clear();
	for(auto e:lines) {
		auto pos = e.find("function ");
		if(pos != std::string::npos) {
			functname.push_back(e.substr(pos + l, e.find("(") - pos - l));
			n++;
		}
	}
	// set log folder
	std::string::size_type len, l1 = filename.find_last_of('/'), l2 = filename.find_last_of('\\');
	if (l1==std::string::npos and l2==std::string::npos) {
        logfolder = "";
    } else {
		if(l1==std::string::npos) {
            len=l2;
        } else if (l2==std::string::npos) {
            len = l1;
        } else {
            len = l1 > l2 ? l1 : l2;
        }
		logfolder = filename.substr(0,len+1);
	}
	// initialize script interpreter
	scriptprocessor script(print_debug_msg,data_capacity,logfolder);
	for(;;) {
		colorset(lightwhite);
		clearscreen(pos.X,pos.Y,w,h,' ');
		gotoxy(pos);
		//select function name
		std::vector<std::string>::size_type i=0;
		for (auto e:functname) {
            std::cout<<"("<<i++<<") function "<<e<<std::endl;
        }
		std::cout<<"select function"<<std::endl;
		std::cout<<">>> ";
		std::cin>>tempstr;
		i = 0;
		if (isdigit(tempstr[0])) {
            i = stoi(tempstr);
        } else {
            for(auto e:functname) {
                if (e==tempstr) {
                    break;
                }
                ++i;
            }
        }
		//run script interpreter
		if(i>=0&&i<n) {
			script.scriptlines(functname[i],lines);
			if(getxy().X != 0) {
                printf("\n");
            }
			system("pause");
		} else {
            break;
        }
	}
	return 0;
}

int scriptshell(int print_debug_msg) {
	std::string tempstr;
	for(;;) {
		colorset(lightwhite);
		clearScreen();
		std::cout << "input filename or \"new\"" << std::endl << ">>> ";
		std::cin >> tempstr;
		auto y = getxy().Y;
		int w = ScreenX, h = ScreenY - y - 1;
		if (scriptshell(tempstr,print_debug_msg,32, {0,y},w,h)) {
            break;
        }
	}
	printf("terminated\n");
    return 0;
}
