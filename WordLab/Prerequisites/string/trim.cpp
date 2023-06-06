std::string trim(std::string s, const std::string whitespace) {
	if (s.empty()) {
        return s;
    }
	s.erase(0, s.find_first_not_of(whitespace));
	s.erase(s.find_last_not_of(whitespace) + 1);
	return s;
}
