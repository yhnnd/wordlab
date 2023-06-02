string ChineseRedirect(const string line, int &lth, int &LineNumber) {

    const bool ignoreCase = false;

	string target_cmd_name = "@target=\"",target_cmd_value = "";
	auto target_cmd_begin = line.find(target_cmd_name);
	auto target_cmd_value_begin = target_cmd_begin + target_cmd_name.length();
	decltype(target_cmd_begin) target_cmd_value_lth;
	if( target_cmd_begin != string::npos ){//TARGET COMMAND (COMMAND NAME) FOUND
		target_cmd_value_lth = line.substr(target_cmd_value_begin).find("\"");
		if(target_cmd_value_lth != string::npos){//TARGET VALUE FOUND
			target_cmd_value = line.substr(target_cmd_value_begin,target_cmd_value_lth);
			if( target_cmd_value == line.substr(0,line.find(" "))){
				// TARGET VALUE IS THE WORD ITSELF
				return "TARGET IS ILLEGAL";
			}
			lth = target_cmd_value_lth;
			LineNumber = Search(target_cmd_value.c_str(), target_cmd_value_lth, ignoreCase);
			if(LineNumber>0){
				return "";//TARGET REDIRECT SUCCESS
			} else if( LineNumber==0 ){
				return "TARGET VALUE \"" + target_cmd_value + "\" NOT FOUND IN DATABASE";
			} else {
				return "TARGET VALUE \"" + target_cmd_value + "\" HAS NO MATCHED DATABASE";
			}
		} else {
			return "NO TARGET VALUE";
		}
	} else {
		return "NO TARGET";
	}
	return "DEFAULT";
}
