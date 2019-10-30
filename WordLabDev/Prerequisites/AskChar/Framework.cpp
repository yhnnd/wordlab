template <typename... Args>
int AskChar(std::string& msg,std::string s,const Args&... rest){
	msg += s;
	return AskChar(msg,rest...);
}
template <typename... Args>
int AskChar(std::string s,const Args&... rest){
	std::string msg="";
	return AskChar(msg,s,rest...);
}
