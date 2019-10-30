void AddWord(const string word){
	int lth = word.length();
	if(word.length()==0) return;
	Dialog.output("start");
	if(Search(word.c_str())>0) return AddWordPrintErrorMessage(7,word);//already added
	// initializing database writer
	ofstream foutEN,foutCH,flog;
	Library(foutEN,lth,EN);// Open Word English Database
	Library(foutCH,lth,CH);// Open Word Chinese Database
	flog.open(AddWordLog,std::ios::app);// Open Log File Stream
	if(AddIsSecure(foutEN,foutCH)){
		// INPUT DEFINITIONS AND SAVE THEM TO DATABASE
		AddWordCore(word,foutEN,foutCH,flog);
		foutEN.close();// Close Word English Database
		foutCH.close();// Close Word Chinese Database
		flog.close();// Close Log File Stream
		// Warning: MUST close the database before sorting the database
		sortlib(lth,lth,DatabaseAdminName,DatabaseAdminPassword);
	}else{
		AddWordPrintErrorMessage(4);//database error
		foutEN.close();
		foutCH.close();
	}
	wait(-1,100,0);
	Dialog.output("reset");
}
