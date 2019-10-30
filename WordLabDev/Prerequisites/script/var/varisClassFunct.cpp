int scriptprocessor::varIsClassFunct(const std::string & name,const std::string & value,const std::string & line){
	return line.find("var")==0
	&& name.length()
	&& value.find("function(")==0;
}
