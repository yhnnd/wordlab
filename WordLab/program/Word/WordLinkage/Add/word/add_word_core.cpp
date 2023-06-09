int addWordAndDefs(const string word, const int lth, const string defs) {
    if (db_is_secure(false, false) == false) {
        return -1;
    }
    string word_and_defs = "";
    const auto wordPos = defs.find(word + " ");
    if (wordPos == std::string::npos || wordPos > 0) {
        word_and_defs = word + " " + defs;
    } else {
        word_and_defs = defs;
    }
    ofstream foutEN, foutCH, flog;
    Library(foutEN,lth,EN);// Open word English database
    Library(foutCH,lth,CH);// Open word chinese database
    flog.open(AddWordLog, std::ios::app);// Open Log File Stream
    if (foutEN && foutCH && flog) {
        foutEN << endl << word;// Add word to DB
        foutCH << endl << word_and_defs;// Add Def to DB
        // write log file
        flog << endl << "<time>" << getCurrentTime();
        flog << endl << "<word>" << word;
        flog << endl << "<defs>" << defs << endl;

        foutEN.close();
        foutCH.close();
        flog.close();

        sortlib(lth, lth, DatabaseAdminName, DatabaseAdminPassword);
        return 0;
    } else {
        foutEN.close();
        foutCH.close();
        flog.close();
        return -2;
    }
}

void addWordCore(const string word, ofstream &foutEN, ofstream &foutCH, ofstream &flog, const enum AddMode mode) {
    string line_of_defs = "";
    if (mode == AddMode::AddWord) {
        // start entering definition
        line_of_defs = AddWordGetTranslation(word);
    } else if (mode == AddMode::RedirectWord) {
        Dialog.output("input target:");
        string target = "";
        ::fflush(stdin);
        getline(cin, target);
        line_of_defs = ",/redirected./@target=\"" + target + "\";";
    }
//	cout<< "you are going to add word '" << word << "' and defs '" << line_of_defs << "' to db";
//	getch();
	if (line_of_defs.length()) {
		// Prepare to Add word and Definition to DB
		AddWordPrintMessage(8, word + " " + line_of_defs);

        ::fflush(stdin);
        std::cin.clear();
        std::cin.sync();
        const char key = getch();

		if (key == 13 || key == 10) {
			foutEN << endl << word;// Add word to DB
			foutCH << endl << word << " " << line_of_defs;// Add Def to DB
			// write log file
			flog << endl << "<time>" << getCurrentTime();
			flog << endl << "<word>" << word;
			flog << endl << "<defs>" << line_of_defs << endl;
		} else {
			AddWordPrintErrorMessage(1);//addition cancelled
		}
	} else {
		AddWordPrintErrorMessage(8);//no definition
	}
}
