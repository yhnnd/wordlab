void window::save(std::string begin,std::string end){
	std::ofstream fout(title,std::ios::trunc);
	for(int i=0;i<text.size();++i){
		//begin not found
		if(strncmp(text.line(i),begin.c_str(),begin.length())!=0){
			fout<<begin;
		}
		//put line
		fout<<text.line(i);
		//end not found
		if(strncmp(text.line(i)+strlen(text.line(i))-end.length(),end.c_str(),end.length())!=0){
			fout<<end;
		}
		if(i<text.size()-1) fout<<std::endl;
	}
	fout.close();
}
