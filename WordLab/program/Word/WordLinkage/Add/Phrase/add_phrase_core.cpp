std::string addPhraseInputNormalDefinitions() {
    const vector<string> msgs = {"", "", "", "    continue appending definitions ?", "", "", "", "", ""};
    const int x = 20, y = 8, width = 40;
    string defs = "";
    for (;;) {
        defs = "";
        for (;;) {
            Dialog.output("input definition:");

            {
                std::string def = "";

                ::fflush(stdin);
                std::getline(cin, def);

                defs += def;
            }

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
        const char ch1 = getch();

        if (ch1 == 13 || ch1 == 10) {
            break;// break outer loop
        } else {
            Dialog.output("input definitions anew ?");
            const char ch2 = getch();
            if (ch2 == 13 || ch2 == 10) {
                continue;
            } else {
                defs = "";
                break;
            }
        }
    }
    return defs;
}


std::string addPhraseInputRedirectTarget () {
    std::string defs = "";
    for (;;) {
        std::string target = "";
        Dialog.output("input target:");

        ::fflush(stdin);
        std::getline(cin, target);

        Dialog.output("use target \"" + target + "\" ?");

        ::fflush(stdin);
        const char ch3 = getch();

        if (ch3 == 13 || ch3 == 10) {
            defs = "/redirected./@target=\"" + target + "\"";
            break;
        } else {
            Dialog.output("input target anew ?");
            const char ch4 = getch();
            if (ch4 == 13 || ch4 == 10) {
                continue;
            } else {
                defs = "";
                break;
            }
        }
    }
    return defs;
}


int addPhraseCore(const string msg, const enum AddMode mode) {

    const auto inputDefinitions = [&mode] () -> std::string {
        if (mode == AddMode::AddPhrase) {
            return addPhraseInputNormalDefinitions();
        } else if (mode == AddMode::RedirectPhrase) {
            return addPhraseInputRedirectTarget();
        } else {
            return "";
        }
    };

    const std::string definitions = inputDefinitions();

    if (definitions.empty()) {
        return 0;
    }

	std::string s = "," + msg + "," + definitions + ";";

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
