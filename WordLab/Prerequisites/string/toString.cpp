template <typename T>
std::string toString(const T & object) {
	std::string s;
	std::stringstream ss;
	ss << object;
	ss >> s;
	return s;
}
