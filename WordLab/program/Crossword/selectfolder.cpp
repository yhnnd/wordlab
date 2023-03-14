string CrosswordSelectFolder(const string folder) {
	const char* tempfilename("dir.tmp");
	//write all filenames in folder to temp file
	FILE* fp=fopen(tempfilename,"w+");
	folderdir((folder + "puzzle").c_str(),fp);
	int l=filelines(fp,0,1);
	fclose(fp);
	//read filenames from temp file
	if(l<=0){
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
		string selectOneFromManyOptions (vector<string>, string);
		string filename = selectOneFromManyOptions(lines, "input a number or name: ");
		return folder + filename;
	}
	return folder;
}

string selectOneFromManyOptions (vector<string> lines, string message) {
	int nol = 0;
	for_each(lines.begin(), lines.end(), [&nol](string line) {
		nol++;
		cout << nol << " " + line << endl;
	});
	cout << message;
	string line;
	cin >> line;
	int n = toint(line);
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
