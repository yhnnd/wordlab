template <typename T>
std::string toString(const T & object) {
	std::string line = "";
	std::stringstream ss;
	ss << object;
	std::getline(ss, line);
	return line;
}
