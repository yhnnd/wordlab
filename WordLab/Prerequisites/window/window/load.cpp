void window::load(std::string begin,std::string end){
	std::ifstream fin(title);
	std::string line;
	for(int n=0;n<text.capacity()&&!fin.eof();text.setsize(++n)){
		if(getline(fin,line)){
			//get line
			strncpy(text.line(n),line.c_str(),_min(line.length(),text.linecapacity()));
			//begin found
			if(strncmp(text.line(n),begin.c_str(),begin.length())==0){
				strcpy(text.line(n),text.line(n)+begin.length());//erase begin
			}//end found
			if(strncmp(text.line(n)+strlen(text.line(n))-end.length(),end.c_str(),end.length())==0){
				text.line(n)[strlen(text.line(n))-end.length()]=0;//erase end
			}
		}
	}
	fin.close();
}
