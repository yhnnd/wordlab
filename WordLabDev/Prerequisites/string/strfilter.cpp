std::string strfilter(std::string line,std::string pattern,std::string replacewith){
	std::string::size_type i;
	while((i=line.find(pattern))!=std::string::npos){
		line.erase(i,pattern.length());
		line.insert(i,replacewith);
	}
	return line;
}
