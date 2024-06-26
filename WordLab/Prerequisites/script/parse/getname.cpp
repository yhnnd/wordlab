// 获取 "var name = value" 中的 name
std::string scriptprocessor::getname(const std::string & line){
	std::string key = "var";
	int r = 0, begin = line.find(key);
	name = "";
	begin = (begin >= 0) ? begin + key.length() + 1 : 0;
	int end = line.find("=");
	if( end == std::string::npos ) end = line.length();
	for(r = 0; begin < end; begin++ ) name += line[begin];
	consolelog("getting name (%s)",name);
	return name;
}
