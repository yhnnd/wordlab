string WLChineseCore(string line, const int fontcolor) {
	string result_line = "";
	int ver = 0;
	bool flagdef = false, flagsort = false;
	for(int r = 0; r<line.length(); r++) {
		if (line[r] == ',') {
            flagdef = true;
        } else if (line[r]=='/') {
			if ((flagsort=!flagsort)==true) {
                result_line += "<blk-ylw>(";
            } else {
				result_line += ")<" + getChineseColorCommandByNumber(fontcolor) + ">(";
			}
		} else if (line[r]=='@') {
			result_line += line.substr(r,line.substr(r).find(";"));
			r += line.substr(r).find(";")+1;
			goto endDef;
		} else if(line[r]==';') {
endDef:
			result_line += ")";
			flagdef=false;
			ver++;
		} else {
            result_line += line[r];
        }
	}
	result_line += "<";
	result_line += ver > 0 ? "blk-grn" : "blk-red";
	result_line += ">(v)<";
	result_line += ver > 0 ? "blk-ylw" : "blk-red";
	result_line += ">(" + toString(ver) + ")";
	return result_line;
}