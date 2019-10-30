void _table::readlabels(std::istream & is){
	std::string s;
	size_t m,n,p;
	while(getline(is,s)){
		if(( m = s.find("=") ) == std::string::npos ) break;
		if(( n = s.find("\"") )== std::string::npos ) break;
		if(( p = s.substr(n+1).find("\"") )==std::string::npos ) break;
		labels[s.substr(0,m)]=s.substr(n+1,p);
	}
}
void _table::readlabels(std::string const & filename){
	std::ifstream fin(filename.c_str());
	readlabels(fin);
	fin.close();
}
