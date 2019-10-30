int find(std::string msg,const std::string filename){
	int n=0;
	std::string msgfile;
	std::ifstream fin(filename);
	if(!fin.is_open()){
		errorlog("findinfile","cannot open ",filename);
		return 0;
	}
	while(std::getline(fin,msgfile)) if(msg.find(msgfile)!=std::string::npos) n++;
	fin.close();
	return n;
}
