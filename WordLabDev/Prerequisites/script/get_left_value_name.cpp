std::string scriptprocessor :: get_left_value_name(const std::string & lval) {
	std::vector<int> begins;
	std::vector<int> ends;
	if(lval.find('[')!=std::string::npos
	        &&lval.find(']')!=std::string::npos) {
		for(auto i = lval.cbegin(); i != lval.cend(); ++i) {
			if(*i=='[') {
				begins.push_back(i-lval.cbegin());
			} else if(*i==']') {
				ends.push_back(i-lval.cbegin());
			}
		}
	}
	std::string real_name(lval);
	if(begins.size() > 0 && ends.size() > 0 && begins.size() == ends.size()) {
		for(int i = 0; i < begins.size(); ++i) {
			auto begin = begins[i];
			auto end = ends[i];
			std::string value_name = lval.substr(begin+1,end-begin-1);
			if(dataset.has(value_name)) {
				real_name.erase(begin+1,end-begin-1);
				real_name.insert(begin+1,dataset.getvalue(value_name));
			}
		}
	}
	return real_name;
}
