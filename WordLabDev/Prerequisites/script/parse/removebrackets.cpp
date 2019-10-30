std::string scriptprocessor::removebrackets(std::string & s,const std::string & brbegin,const std::string & brend){
	if(s.find(brbegin)==0) s.erase(0,brbegin.length());
	auto i = s.find(brend);
	if(i!=std::string::npos) s.erase(i);
	return s;
}
