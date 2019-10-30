template <typename... Args>
char popup(std::string& msg,std::string s,const Args&... rest){
	msg+=s;
	return popup(msg,rest...);
}
template <typename... Args>
char popup(std::string s,const Args&... rest){
	std::string msg="";
	return popup(msg,s,rest...);
}
