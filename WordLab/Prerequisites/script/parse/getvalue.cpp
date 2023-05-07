// get value of statement "var name = value"
std::string scriptprocessor::getvalue(const std::string & line){
	int r = 0, begin = line.find("="), end = 0;
	value = "";
	if (begin >= 0) {
        begin++;
    } else {
        return value;
    }
	for( end = begin; end < line.length() && line[end]!=';' && line[end]!=EOF; end++ ) {

    }
	for( ; begin < end; begin++ ) {
        value += line[begin];
    }
	consolelog("getting value (%s)",value);
	return value;
}

std::string scriptprocessor::getDataByName(const std::string & name) {
    return this->dataset.getvalue(name);
}
