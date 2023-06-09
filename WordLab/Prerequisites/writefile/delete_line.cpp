int DeleteLine(const std::string route, const int n, const bool LastLineNoReturn) {
	const bool DELETE_LAST_LINE = (n == fileLines(route, 1));

	const std::string bufFilename = "buf.txt";

	std::ifstream fin(route);

	std::ofstream fbuf(bufFilename, std::ios::trunc);

	if (fin.fail()) {
        errorLog("deleteline", "cannot open", route);
		return -1;
	}

	if (fbuf.fail()) {
        fin.close();
        errorLog("deleteline", "cannot open buf file", bufFilename);
		return -2;
	}

	int NOL = 0;
	std::string line = "";
	while (!fin.eof()) {
		if (std::getline(fin, line)) {
            NOL++;
        }
		if (NOL != n) {
			fbuf << line;
			// the last line of file has no '\n'
			if(LastLineNoReturn && (fin.eof() || (DELETE_LAST_LINE && NOL == n - 1))) {
                break;
            }
			fbuf << std::endl;
		}
	}
	fin.close();
	fbuf.close();
	remove(route.c_str());
	return rename(bufFilename.c_str(), route.c_str());
}
