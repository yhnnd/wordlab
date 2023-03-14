//	[support]	[functions]
//	menu		search() new_menu() quit()
//	scripts		some scripts
//	launch		function_name()
int Menu(std::string foldername,int x,int y,int width,int Times,int nprev) {
	char menu[20][LINEMAX];
	int n=0,num_lines=(LANGUAGE==0)?loadmsg((char *)menu,foldername+"en.csv",20,LINEMAX,1,1):
		(LANGUAGE==1)?loadmsg((char *)menu,foldername+"ch.csv",20,LINEMAX,1,1):-1;
	if(num_lines<=0) {
		if(num_lines== 0) errorlog("Menu()","Critical Error: File Lost",foldername);
		if(num_lines==-1) errorlog("Menu()","Critical Error: Unknown Language",tostring(LANGUAGE));
		return num_lines;
	}
	for(;;) {
		colorset(white);
		system("cls");
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
						Menu(_data_dir+msg.substr(a+1,b-a-1),x,y,width,0,0);//RECURSIVE
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
