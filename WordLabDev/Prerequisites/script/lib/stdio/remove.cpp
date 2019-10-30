int scriptprocessor::remove(const char *line){
	name = getparam(line);
	if(name[0]=='\"'){
		value = removebrackets(name,"\"","\"");
	} else value = dataset.getvalue(name);
	return ::remove(value.c_str());
}
