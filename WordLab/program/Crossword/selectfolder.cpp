string CrosswordSelectFolder(const string folder) {
	const char * tempfilename = "dir.tmp";
	// write all filenames in the folder to temp file
	FILE * fp = fopen(tempfilename,"w+");
#ifdef _WIN32
	folderdir((folder + "puzzle").c_str(), fp);
#elifdef __APPLE__
    folderdir(folder.c_str(), fp);
#endif
	int l = filelines(fp,0,1);
	fclose(fp);
	// read filenames from temp file
	if (l <= 0) {
		errorlog("CrosswordSelectFolder()","no folder in",folder);
		return "";
	} else {
		string line;
		vector<string> lines;
		ifstream in(tempfilename);
		if(in.is_open()){
			while(getline(in,line)) {
				lines.push_back(line);
			}
		}
		in.close();
		remove(tempfilename);
		//user select a puzzle
		cout<<"choose one of the puzzles below"<<endl;
        const char * tipsStyled = "input a <grn->(number) or <ylw->(name):";
        const char * tipsPlain = "input a number or name:";
		string selectOneFromManyOptions (const vector<string>, const char *, const char *);
		string filename = selectOneFromManyOptions(lines, tipsStyled, tipsPlain);
		return folder + filename;
	}
	return folder;
}

string selectOneFromManyOptions (const vector<string> lines, const char * messageStyled, const char * messagePlainText) {
	int nol = 0;
    colorrecord(colorPrev);
	for_each(lines.begin(), lines.end(), [&nol](string line) {
		nol++;
        colorset(lightgreen);
        std::cout << std::setfill(' ') << std::setw(3) << "" << nol;
        colorset(lightyellow);
        std::cout << std::setfill(' ') << std::setw(3) << "" << line << endl;
	});
    colorreset(colorPrev);
	bsvline(messageStyled, strlen(messagePlainText));
	string line;
	cin >> line;
	int n = toInt(line);
	if (n > 0 && n <= lines.size()) {
		// user input an order number of an option
		return lines[n - 1];
	} else {
		// user input a name of an option
		auto it = lines.begin();
		while (it != lines.end()) {
			if (*it == line) {
				return *it;
			}
			it++;
		}
	}
	return line;
}
