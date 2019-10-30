int DeleteLine(const std::string route,const int n,bool LastLineNoReturn){
	bool DELETE_LAST_LINE=(n==filelines(route,1));
	std::string bufname="buf.txt";
	std::ifstream fin(route);
	std::ofstream fbuf(bufname,std::ios::trunc);
	if(fin.fail()){
		errorlog("deleteline","cannot open",route);
		return -1;
	}
	if(fbuf.fail()){
		errorlog("deleteline","cannot open buf file",bufname);
		return -2;
	}
	int NOL=0;
	std::string line;
	while(!fin.eof()){
		if(std::getline(fin,line)) NOL++;
		if(NOL!=n){
			fbuf<<line;
			//the last line of file has no '\n'
			if(LastLineNoReturn&&(fin.eof()||(DELETE_LAST_LINE&&NOL==n-1))) break;
			fbuf<<std::endl;
		}
	}
	fin.close();
	fbuf.close();
	remove(route.c_str());
	return rename(bufname.c_str(),route.c_str());
}
