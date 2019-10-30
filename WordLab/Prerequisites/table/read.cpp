std::istream & operator >>( std::istream & is, _table & t){
	// get first line of file
	std::string temp;
	getline(is,temp);
	is.clear();
	is.seekg(0);
	// if first line indicates that it is a layout file
	if(*(temp.begin())=='+'&&*(temp.end()-1)=='+') t.readtable(is);
	// if first line indicates that it is a data file
	else t.readdata(is);
	return is;
}
