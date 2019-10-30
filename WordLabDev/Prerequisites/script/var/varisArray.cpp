bool scriptprocessor::varIsArray(const std::string & name,const char *line){
	return strindex(line,"var") >= 0
	&& name.find("[") > 0
	&& name.find("[") < name.find("]");
}
