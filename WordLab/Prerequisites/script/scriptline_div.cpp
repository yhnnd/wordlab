int scriptprocessor::scriptline_div(std::string msg,std::string functname){
	if(msg.empty()) return 0;
	if(msg.find(';')==std::string::npos){
		scriptline(msg.c_str(),functname.c_str());
		return 1;
	}
	std::queue<std::string> strs;
	std::string str="";
	bool ForLoop = msg.find("for (")!=std::string::npos || msg.find("for(")!=std::string::npos;
    if (ForLoop) {// keep the original format
        strs.push(msg);
    } else // divide msg by ';'
        for(auto it=msg.begin();it!=msg.end();++it){
            if (*it == ';') {
                strs.push(str);
                str = "";
            } else str += *it;
        }

    while(strs.size()){
		scriptline(strs.front().c_str(),functname.c_str());
		strs.pop();
	}
    return 0;
}
