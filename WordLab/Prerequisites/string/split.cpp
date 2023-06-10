std::vector<std::string> split(const std::string &line, const std::string &separators) {
	using namespace std;
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while(i != line.size()) {
		// find first char which is not separator
		int flag = 0;
		while(i != line.size() && flag == 0) {
			flag = 1;
			for(string_size x = 0; x < separators.size(); ++x) {
				if (line[i] == separators[x]) {
					++i;
					flag = 0;
					break;
				}
			}
		}

		// find another separator
		flag = 0;
		string_size j = i;
		while (j != line.size() && flag == 0) {
			for (string_size x = 0; x < separators.size(); ++x) {
				if (line[j] == separators[x]) {
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
                ++j;
            }
		}
		if (i != j) {
			result.push_back(line.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

std::string join(const std::vector<std::string> src, const std::string joinWith) {
    std::string res = "";
    if (src.size() == 0) {
        return res;
    }

    std::vector<std::string>::const_iterator it = src.begin();
    res += *it;

    for (it++; it!=src.end(); it++) {
        res += joinWith;
        res += *it;
    }
    return res;
}

std::string replace(const std::string src, const std::string subStr, const std::string replaceWith) {
    std::string s = src;
    size_t pos = 0;
    while ((pos = s.find(subStr, pos)) != std::string::npos) {
        s.erase(pos, subStr.length());
        s.insert(pos, replaceWith);
        pos += replaceWith.length();
    }
    return s;
}