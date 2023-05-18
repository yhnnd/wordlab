void AddWord(const string word) {
	int lth = word.length();
	if(word.length() == 0) {
		return;
	}
	Dialog.output("start");
	if (Search(word.c_str(), word.length()) > 0) {
		return AddWordPrintErrorMessage(7,word);//already added
	}
	// initializing database writer
	ofstream foutEN, foutCH, flog;
	Library(foutEN,lth,EN);// Open word English database
	Library(foutCH,lth,CH);// Open word chinese database
	flog.open(AddWordLog, std::ios::app);// Open Log File Stream
	if (AddIsSecure(foutEN,foutCH)) {
		// INPUT DEFINITIONS AND SAVE THEM TO DATABASE
		AddWordCore(word,foutEN,foutCH,flog);
		foutEN.close();// Close word English database
		foutCH.close();// Close word chinese database
		flog.close();// Close Log File Stream
		// Warning: MUST close the database before sorting the database
		sortlib(lth,lth,DatabaseAdminName,DatabaseAdminPassword);
	} else {
		AddWordPrintErrorMessage(4);//database error
		foutEN.close();
		foutCH.close();
        flog.close();
	}
	wait(-1, 100, 0);
	Dialog.output("reset");
}