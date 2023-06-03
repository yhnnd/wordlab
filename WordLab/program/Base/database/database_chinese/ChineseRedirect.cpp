string ChineseRedirect(const string line, int &lth, int &LineNumber) {

    const bool ignoreCase = false;

	const std::string target_cmd_name = "@target=\"";
	const std::string::size_type target_cmd_begin = line.find(target_cmd_name);
	const std::string::size_type target_cmd_value_begin = target_cmd_begin + target_cmd_name.length();

	if ( target_cmd_begin != string::npos ) {// TARGET COMMAND (COMMAND NAME) FOUND
		const std::string::size_type target_cmd_value_lth = line.substr(target_cmd_value_begin).find("\"");
		if (target_cmd_value_lth != string::npos) {// TARGET VALUE FOUND
			const std::string target_cmd_value = line.substr(target_cmd_value_begin, target_cmd_value_lth);
			if ( target_cmd_value == line.substr(0, line.find(" "))) {
				// TARGET VALUE IS THE WORD ITSELF
				return "TARGET IS ILLEGAL";
			}

            if (target_cmd_value.find(" ") == string:: npos) {
                // Target Value is of type word.
                lth = target_cmd_value_lth;
                LineNumber = Search(target_cmd_value.c_str(), target_cmd_value_lth, ignoreCase);
            } else {// Target Value is of type phrase.
                return "PHRASE " + target_cmd_value;
            }
			if (LineNumber > 0) {
				return "";//TARGET REDIRECT SUCCESS
			} else if ( LineNumber == 0 ) {
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
