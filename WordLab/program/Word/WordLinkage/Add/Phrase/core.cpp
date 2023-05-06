int AddPhraseCore(const string msg) {
	int r = 0, n = 1;
	auto def = [] {
		Dialog.output("input definition:");
		string def = "";
		cin >> def;
		return def;
	};
	string s = "," + msg + "," + def() + ";";
	for(auto p=s.begin(); p != s.end(); p++) {
		if (*p == ' ') {
			n++;
			*p = ',';
		}
	}
	Dialog.output("add \""+s+"\" to library?");
    const char ch = getch();
	if (ch == 13 || ch == 10) {
		string route=PhraseRouteA;
		route += toString(n);
		route += PhraseRouteB;
		ofstream fout(route,ios::app);
		if(fout.is_open()) {
			fout << s << endl;
			fout.close();
			Dialog.output("Phrase \"" + s + "\" Added.");
		} else {
            Dialog.output("cannot open file "+route);
        }
	} else {
        Dialog.output("Addition Cancelled");
    }
    return 0;
}
