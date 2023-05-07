void AddWordCore(string word, ofstream &foutEN, ofstream &foutCH, ofstream &flog) {
	// start entering definition
	string line_of_defs = AddWordGetTranslation(word);
//	cout<< "you are going to add word '" << word << "' and defs '" << line_of_defs << "' to db";
//	getch();
	if (line_of_defs.length()) {
		// Prepare to Add word and Definition to DB
		AddWordPrintMessage(8, word + " " + line_of_defs);
        const char key = getch();
		if (key == 13 || key == 10) {
			foutEN<<endl<<word;// Add word to DB
			foutCH<<endl<<word<<" "<<line_of_defs;// Add Def to DB
			// write log file
			flog<<endl<<"<time>"<<getCurrentTime();
			flog<<endl<<"<word>"<<word;
			flog<<endl<<"<defs>"<<line_of_defs<<endl;
		} else {
			AddWordPrintErrorMessage(1);//addition cancelled
		}
	} else {
		AddWordPrintErrorMessage(8);//no definition
	}
}
