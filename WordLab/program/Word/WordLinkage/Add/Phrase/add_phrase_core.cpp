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

                if (defs != "" && def != "") {
                    defs += ",";
                }

                defs += def;
            }

            const int choice = MessageWindow.Confirm(2, x, y, width, msgs);

            if (choice != 1) {
                break;// break inner loop
            } else {
                Dialog.output("\"" + defs + "\"");
            }
        }

        if (defs.empty() == false && [&defs] () -> bool {
            Dialog.output("use definitions \"" + defs + "\" ?");

            ::fflush(stdin);
            cin.clear();
            cin.sync();
            const char ch1 = getch();

            return (ch1 == 13 || ch1 == 10);
        }()) {
            break;// break outer loop
        } else {
            Dialog.output("input definitions anew ?");

            ::fflush(stdin);
            cin.clear();
            cin.sync();
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
        cin.clear();
        cin.sync();
        const char ch3 = getch();

        if (ch3 == 13 || ch3 == 10) {
            defs = "/redirected./@target=\"" + target + "\"";
            break;
        } else {
            Dialog.output("input target anew ?");

            ::fflush(stdin);
            cin.clear();
            cin.sync();
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

    const std::string definitions = [&mode] () -> std::string {
        if (mode == AddMode::AddPhrase) {
            return addPhraseInputNormalDefinitions();
        } else if (mode == AddMode::RedirectPhrase) {
            return addPhraseInputRedirectTarget();
        } else {
            return "";
        }
    }();

    if (definitions.empty()) {
        Dialog.output("add phrase cancelled");
        return 0;
    }

    const std::vector<std::string> phraseToAdd = split(msg, " ");

	const std::string line = "," + join(phraseToAdd, ",") + "," + definitions + ";";

	Dialog.output("add \"" + line + "\" to library?");

    ::fflush(stdin);
    const char ch = getch();

	if (ch == 13 || ch == 10) {
		const std::string route = PhraseRouteA + toString(phraseToAdd.size()) + PhraseRouteB;
		ofstream fout(route, ios::app);
		if (fout.is_open()) {
			fout << line << endl;
			fout.close();
			Dialog.output("Phrase \"" + line + "\" Added.");
		} else {
            Dialog.output("cannot open file " + route);
        }
	} else {
        Dialog.output("Addition Cancelled");
    }
    return 0;
}
