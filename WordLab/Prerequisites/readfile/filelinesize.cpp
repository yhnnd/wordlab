std::string::size_type fileLineSize(const std::string filename) {
	std::ifstream fin(filename);
	std::string::size_type lineSize = 0;
	if (fin) {
		std::string line = "";
		while (std::getline(fin, line)) {
			if (line.length() > lineSize ) {
                lineSize = line.length();
            }
		}
	}
	fin.close();
	return lineSize;
}
