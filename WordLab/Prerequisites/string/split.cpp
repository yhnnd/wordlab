std::vector<std::string> split(const std::string &line, const std::string &seperator) {
	using namespace std;
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while(i != line.size()) {
		// find first char which is not seperator
		int flag = 0;
		while(i != line.size() && flag == 0) {
			flag = 1;
			for(string_size x = 0; x < seperator.size(); ++x) {
				if (line[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
			}
		}

		// find another seperator
		flag = 0;
		string_size j = i;
		while(j != line.size() && flag == 0) {
			for(string_size x = 0; x < seperator.size(); ++x) {
				if(line[j] == seperator[x]) {
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
                ++j;
            }
		}
		if (i != j) {
			result.push_back(line.substr(i, j-i));
			i = j;
		}
	}
	return result;
}
