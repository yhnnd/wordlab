template <typename T> int toInt(const T& object) {
	int i;
	std::stringstream ss;
	ss << object;
	ss >> i;
	return i;
}
