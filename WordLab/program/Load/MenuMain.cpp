int Menu(std::string foldername,int x,int y,int width,int Times,int nprev){
	char menu[20][LINEMAX];
	bool flag=0;
	flag=(LANGUAGE==0)?loadmsg((char *)menu,foldername+"en.csv",20,LINEMAX,1):
		 (LANGUAGE==1)?loadmsg((char *)menu,foldername+"ch.csv",20,LINEMAX,1):-1;
	if(flag== 0) errorlog("Menu()","Critical Error: File Lost",foldername);
	if(flag==-1) errorlog("Menu()","Critical Error: Unknown Language",tostring(LANGUAGE));
	if(flag<=0) return flag;
	int n = multitask(x,y,width,menu,Times,nprev);
	std::string temp_menu(menu[n]),temp_cmd;
	std::string::size_type pos;
	const unsigned int num_cmds=3;
	std::string cmds[num_cmds]={"menu","scripts","launch"};
	for(int i=0;i<num_cmds;i++){
		temp_cmd=","+cmds[i]+",";
		pos=temp_menu.find(temp_cmd);
		if(pos!=std::string::npos){
			pos+=temp_cmd.length();
			if(i==0){//menu
				auto s=temp_menu.substr(pos);
				if(s.find("new_menu(")==0){
					auto a=s.find("("),b=s.find(")");
					Menu(s.substr(a+1,b-a-1),x,y,width,0,0);
				}
			}else if(i==1) ;//scripts
			else if(i==2) launch(temp_menu.substr(pos));
		}
	}
	//	if(n==5) Load.DeveloperTools();
	//	else if(n==6) Load.UserLaunch();
	//	else if(n==7) Load.Settings();
	return n;
}
