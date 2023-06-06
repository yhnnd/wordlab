std::string strFilter(std::string line, std::string pattern, std::string replaceWith) {
	std::string::size_type i;
	while ((i = line.find(pattern)) != std::string::npos) {
		line.erase(i, pattern.length());
		line.insert(i, replaceWith);
	}
	return line;
}
