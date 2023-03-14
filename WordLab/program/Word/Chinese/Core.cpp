string WLChineseCore(string line,int fontcolor) {
	string result_line = "";
	int ver = 0;
	bool flagdef = false, flagsort = false;
	for(int r = 0; r<line.length(); r++) {
		if(line[r]==',') flagdef = true;
		else if(line[r]=='/') {
			if((flagsort=!flagsort)==true) {
                result_line += "<"+getcolorBcmd(2)+">(";
            } else {
				result_line += ")";
				if(fontcolor==1) result_line += "<clrful->(";
				else result_line += "<"+getChineseColorCommandByNumber(fontcolor)+">(";
			}
		} else if(line[r]=='@') {
			result_line += line.substr(r,line.substr(r).find(";"));
			r += line.substr(r).find(";")+1;
			goto enddef;
		} else if(line[r]==';') {
enddef:
			result_line += ")";
			flagdef=false;
			ver++;
		} else result_line += line[r];
	}
	result_line += "<";
	result_line += ver>0? getcolorBcmd(3):getcolorBcmd(1);
	result_line += ">(v)<";
	result_line += ver>0? getcolorBcmd(2):getcolorBcmd(1);
	result_line += ">(" + tostring(ver) + ")";
	return result_line;
}
