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
        errorLog("CrosswordSelectFolder()", "no folder in", folder);
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
        const char * tipsStyled = "press <grn-blk>([W] [A] [S] [D]) to switch and press <grn-blk>([Enter]) to confirm";
		string selectOneFromManyOptions (const vector<string>, const char *);
		string filename = selectOneFromManyOptions(lines, tipsStyled);
        if (filename.empty()) {
            return "";
        } else {
            return folder + filename;
        }
	}
}

string selectOneFromManyOptions (const vector<string> lines, const char * message) {
	const int x = 2, y = 1;
    gotoxy(x, y + lines.size() + 3);
	bsvLine(message);
    vector<string> menu;
    char s[128];
    for (const auto & line: lines) {
        snprintf(s, sizeof(s), "%-58s", line.c_str());
        menu.push_back(s);
    }
    const int n = chooseFromMenu({x, y}, 60, menu);
	if (n >= 0 && n < lines.size()) {
        return lines[n];
    } else {
        return "";
    }
}
