// 获取 "function(param)" 中的 param
std::string scriptprocessor::getparam(const std::string & line) {
	bool inString = 0, inChar = 0;
	std::string param = "";
	for( int i = line.find("(") + 1; i < line.length(); i++ ) {
		if(line[i]=='\''&&line[i-1]!='\\') deny(inChar,inChar);
		else if(line[i]=='\"'&&line[i-1]!='\\') deny(inString,inString);
		else if(!inChar&&!inString&&(line[i]==','||line[i]==')')) break;
		param += line[i];
	}
	consolelog("getting param %s",param);
	return param;
}

