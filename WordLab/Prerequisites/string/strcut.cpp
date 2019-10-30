//obsolete
const char *strtrim(std::string src,int begin,int end){
	if(begin<0) begin=0;
	if(end<=0) end=src.length();
	std::string dst=src.substr(begin,end-begin);
	return dst.c_str();
}
