int MessageWindowLoad(tablerow *item, const char *filename) {
	int r = 1;
    std::string line = "";
	std::ifstream fin(filename);
	if (fin) {
        while (std::getline(fin, line)) {
            r = item[r].Load(r, line.c_str());
        }
        fin.close();
    } else {
        return 0;
    }

	return r - 1;
}
