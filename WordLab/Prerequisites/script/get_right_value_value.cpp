float scriptprocessor :: get_right_value_value(const std::string & rval) {
	std::string rval_parsed(rval);
	std::vector<std::string> var_names = split(rval, "+-*/%^<>!=()");
	for(auto i = 0; i != var_names.size(); ++i) {
		float var_value;
		std::string var_value_str;
		if(isdigit(var_names[i][0])) {
			var_value_str = var_names[i];
		} else {
			var_value = maths::calc(dataset.getvalue(var_names[i]).c_str());
			var_value_str = toString(var_value);
		}
		auto var_name_pos = rval_parsed.find(var_names[i]);
		auto var_name_length = var_names[i].length();
		rval_parsed.erase(var_name_pos,var_name_length);
		rval_parsed.insert(var_name_pos,var_value_str);
	}
	return maths::calc(rval_parsed);
}
