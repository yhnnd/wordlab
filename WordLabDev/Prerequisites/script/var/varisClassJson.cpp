int scriptprocessor::varIsClassJson(const std::string & name,const std::string & value,const std::string & line){
	return line.find("var") >= 0
	&& value[0] == '{'
	&& value[value.length()-1] == '}';
}
