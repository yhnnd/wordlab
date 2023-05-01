string Chinese(int lth,int lineNumber,int defNumber = 1);
string Chinese(int lth,int lineNumber,int defNumber) {
	int NOL = 0;
	string line, def;
	ifstream fin;
	Library(fin,lth,lang::CH);
	while (!fin.eof()) {
		if (getline(fin,line)) {
            NOL++;
        }
		if (NOL == lineNumber) {
			if (defNumber <= 0) {// return all defs
				def = line;
			} else {// return def#defNumber
				auto begin = line.find("@");
				if (begin != std::string::npos) {
					auto end = line.find_first_of("@;",++begin);
					if (end != std::string::npos) {
						def = line.substr(begin, end - begin);
					}
				}
			}
		    break;
		}
	}
	fin.close();
	return def;
}
