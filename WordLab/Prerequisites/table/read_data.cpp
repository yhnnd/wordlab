void _table::readdata( std::istream & is){
	std::string s,item;
	while(getline(is,s)){
		std::stringstream ss(s);
		_tablerow line;
		while(ss>>item) line.setcol(item.length(),item);
		data.push_back(line);
	}
}
void _table::readdata( std::string const & filename){
	std::ifstream fin(filename.c_str());
	this->datasource.push_back( filename );
	readdata(fin);
	fin.close();
}
