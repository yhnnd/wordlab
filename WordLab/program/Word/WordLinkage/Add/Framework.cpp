void AddNew(const string s) {
	if(s.empty()) return;
	Dialog.output("start");
	for(int TIMES=1; TIMES<=2; TIMES++) {
		AddWordPrintMessage(TIMES,s);
		if(getch()!=13) {
			AddWordPrintErrorMessage(1,s);
			goto end;
		}
	}
	if(Ctype) if(!User.login()) goto end;
	if(s.find(" ")!=std::string::npos) {
		popup("Add Phrase",0);
		AddPhrase(s);
	} else {
		popup("Add word <ylw->(",s,0);
		AddWord(s);
	}
	end:
	wait(-1,10,0);
	Dialog.output("reset");
}
