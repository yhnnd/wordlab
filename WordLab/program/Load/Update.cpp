int load::UpdateDatabase(const string route) {
    const string filenamePrefix = route + "en/english";
    const string filenameDefPrefix = route + "ch/chinese";
    const string filenamePostfix = ".csv";
    bool stopUpdating = false;
    int numOfWordsUpdated = 0;
    molecular Molecular;
    for (int lth = 1; lth <= 30; ++lth) {
        string filename = filenamePrefix + toString(lth) + filenamePostfix;
        string filenameDef = filenameDefPrefix + toString(lth) + filenamePostfix;
//        cout << "filename \"" << filename << "\"" << endl;
        ifstream finDb1(filename);
        ifstream finDbDef(filenameDef);
        if (finDb1 && finDbDef) {
            string line = "", lineDef = "";
            while (std::getline(finDb1, line)) {
//                cout << "line \"" << line << "\"" << endl;
//                getch();
                if (std::getline(finDbDef, lineDef)) {
                    string word = line.substr(0, lth);
                    Molecular.setWord(word.c_str());
                    char def[32] = "";
                    const int result1 = Molecular.getWordDefinitions(def, sizeof(def));
                    if (result1 <= 0 || def[0] == '\0') {
                        const int result2 = Search(word.c_str(), word.length(), false);
                        if (result2 <= 0) {
//                            cout << "word \"" << word << "\" def \"" << lineDef << "\"" << endl;
//                            getch();
                            if (addWordAndDefs(word, lth, lineDef) == 0) {
                                ++numOfWordsUpdated;
                            } else {
                                printf("\nError: word \"%s\" cannot be updated.\n", word.c_str());
                                printf("\nContinue updating?\n");
                                const char key = getch();
                                if (key == 13 || key == 10) {
                                    stopUpdating = false;
                                } else {
                                    stopUpdating = true;
                                }
                            }
                        }
                    }
                } else {
                    break;
                }
            }
            finDb1.close();
            finDbDef.close();
        } else {
            return -1;
        }
        if (stopUpdating == true) {
            return -2;
        }
    }
    return numOfWordsUpdated;
}

void load::UpdateSoftware(string route){

}

void load::Update() {
    int x = 1, y = 6;
#ifdef __APPLE__
    x = 2;
#endif
	MessageWindow.Frame(0,0,2,70,16,16);
    const int width1 = 73;

	gotoxy(x, y);
    bsvline("<-wte>(select a file route", width1);

    ::fflush(stdin);
    gotoxy(x + 17, y);
    string folder = selectOneFromManyOptions({"../WordLabGo/files/lang-utf8/"}, "select a database to update from");

    if (folder.empty()) {
        gotoxy(x, ++y);
        bsvline("<-wte>(update cancelled", width1);
    } else {
        gotoxy(x, ++y);
        bsvline("<-wte>(update database?", width1);

        ::fflush(stdin);
        char c = getch();

        if (c == 13 || c == 10) {
            gotoxy(x, ++y);
            bsvline("<-wte>(<-ylw>(updating) database", width1);
            const int numOfWordsUpdated = UpdateDatabase(folder);
            if (numOfWordsUpdated > 0) {
                gotoxy(x, ++y);
                const string msg1 = "<-wte>(<-grn>(completed.) " + toString(numOfWordsUpdated) + " words updated.";
                bsvline(msg1.c_str(), width1);
            } else if (numOfWordsUpdated == 0) {
                gotoxy(x, ++y);
                bsvline("<-wte>(<-grn>(database is up to date.) no need to update.", width1);
            } else {
                gotoxy(x, ++y);
                bsvline("<-wte>(<-red>(update failed)", width1);
            }
        }

        gotoxy(x, ++y);
        bsvline("<-wte>(update system?", width1);

        ::fflush(stdin);
        c = getch();

        if (c == 13 || c == 10) {
            gotoxy(x, ++y);
            bsvline("<-wte>(<-ylw>(updating) system", width1);
            UpdateSoftware(folder);
            gotoxy(x, ++y);
            bsvline("<-wte>(<-grn>(complete)", width1);
        }
    }

	gotoxy(x, ++y);
	bsvline("<-wte>(all done", width1);
	wait(-1, 100, 0);
	colorreset(lightwhite);
	clearscreen(0,0,76,3);//erase the popup
	clearscreen(0,2,76,18);//erase the panel
}

