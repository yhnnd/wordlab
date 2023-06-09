int addPhraseCore(const string msg, const enum AddMode mode) {

	auto def = [&mode] {
        if (mode == AddMode::AddPhrase) {
            const vector<string> msgs = {"", "", "", "    continue appending definitions ?", "", "", "", "", ""};
            const int x = 20, y = 8, width = 40;
            string defs = "", def = "";
            for (;;) {
                defs = "";
                for (;;) {
                    Dialog.output("input definition:");
                    ::fflush(stdin);
                    cin >> def;
                    defs += def;
                    const int choice = MessageWindow.Confirm(2, x, y, width, msgs);
                    if (choice != 1) {
                        break;// break inner loop
                    } else {
                        defs += ",";
                        Dialog.output("\"" + defs + "\"");
                    }
                }
                Dialog.output("use definitions \"" + defs + "\" ?");
                ::fflush(stdin);
                const char ch = getch();
                if (ch == 13 || ch == 10) {
                    break;// break outer loop
                }
            }
            return defs;
        } else if (mode == AddMode::RedirectPhrase) {
            std::string defs = "";
            for (;;) {
                std::string target = "";
                Dialog.output("input target:");
                std::getline(cin, target);
                Dialog.output("use target \"" + target + "\" ?");
                ::fflush(stdin);
                const char ch = getch();
                if (ch == 13 || ch == 10) {
                    defs = "/redirected./@target=\"" + target + "\"";
                    break;
                }
            }
            return defs;
        } else {
            return std::string ("");
        }
	};

	string s = "," + msg + "," + def() + ";";

    int numOfWords = 1;

	for(auto p = s.begin(); p != s.end(); p++) {
		if (*p == ' ') {
			numOfWords++;
			*p = ',';
		}
	}

	Dialog.output("add \"" + s + "\" to library?");

    ::fflush(stdin);
    const char ch = getch();

	if (ch == 13 || ch == 10) {
		const std::string route = PhraseRouteA + toString(numOfWords) + PhraseRouteB;
		ofstream fout(route, ios::app);
		if (fout.is_open()) {
			fout << s << endl;
			fout.close();
			Dialog.output("Phrase \"" + s + "\" Added.");
		} else {
            Dialog.output("cannot open file " + route);
        }
	} else {
        Dialog.output("Addition Cancelled");
    }
    return 0;
}
