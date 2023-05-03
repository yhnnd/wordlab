//	[support]	[functions]
//	menu		search() new_menu() quit()
//	scripts		some scripts
//	launch		function_name()
int load::mainUserInterface(const std::string foldername,int x,int y,int width,int Times,int nprev) {
	char menu[20][LINEMAX];
	int n = 0, num_lines = -1;
    if (LANGUAGE == EN) {
        num_lines = loadmsg((char *)menu,foldername+"en.csv",20,LINEMAX,1,1);
    } else if (LANGUAGE == CH) {
        num_lines = loadmsg((char *)menu,foldername+"ch.csv",20,LINEMAX,1,1);
    }
	if (num_lines <= 0) {
		if (num_lines == 0) {
            errorlog("Menu()","Critical Error: File Lost",foldername);
        } else if (num_lines == -1) {
            errorlog("Menu()","Critical Error: Unknown Language",toString(LANGUAGE));
        }
#if defined(__APPLE__)
        getch();
#endif
		return num_lines;
	}
	for (;;) {
		colorset(lightwhite);
		clearScreen();
		PrintSoftwareInfo();
		n = multitask(x,y,width,menu,Times,nprev);
		if(n==-1) {
            return n;
        }
		std::string temp_menu(menu[n]),temp_cmd;
		std::string::size_type pos;
		const unsigned int num_cmds=3;
		std::string cmds[num_cmds] = {"menu","scripts","launch"};
		for(int i=0;i<num_cmds;i++) {
			temp_cmd=","+cmds[i]+",";
			pos=temp_menu.find(temp_cmd);
			if(pos!=std::string::npos) {
				auto msg=temp_menu.substr(pos+temp_cmd.length());
				if(i==0) {//menu
					if(msg.find("new_menu(")==0) {
						auto a=msg.find("("),b=msg.find(")");
//                        cout << "about to load menu. folder =" << _data_dir + msg.substr(a+1,b-a-1);
//                        getch();
						mainUserInterface(_data_dir+msg.substr(a+1,b-a-1),x,y,width,0,0);//RECURSIVE
					} else if(msg.find("quit(")==0) {
                        return n;
                    }
				} else if(i==1) {//scripts
					scriptprocessor sp(0,32);
					sp.scriptline_div(msg,"");
				} else if(i==2) {//launch
					launch(msg);
				}
			}
		}
	}
	return n;
}
