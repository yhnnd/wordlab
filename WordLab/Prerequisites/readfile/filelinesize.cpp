std::string::size_type
filelinesize(std::string filename){
	std::ifstream fin(filename);
	std::string::size_type linesize = 0;
	if(fin){
		std::string line;
		while(std::getline(fin,line)){
			if( line.length() > linesize ) linesize = line.length();
		}
	}
	fin.close();
	return linesize;
}
