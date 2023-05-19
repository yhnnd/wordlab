char AddNew(const string s) {
	if(s.empty()) {
        return 0;
    }
//    printf("\nadd new begin\n");
	Dialog.output("start");
//    printf("\nprint dialog\n");
	for(int TIMES=1; TIMES<=2; TIMES++) {
		AddWordPrintMessage(TIMES,s);
        // printf("\nwaiting for getch\n");
		if(getch()!=13) {
			AddWordPrintErrorMessage(1,s);
			goto end;
		}
	}
    // printf("\ncheck user login\n");
	if(Ctype) {
        if(!User.login()) {
            goto end;
        }
    }
	if(s.find(" ")!=std::string::npos) {
//        printf("\nadd new phrase\n");
		popup("Add Phrase",0);
		AddPhrase(s);
	} else {
//        printf("\nadd new word\n");
		popup("Add word <ylw->(",s,0);
		AddWord(s);
	}
	end:
	const char key = getch();
	Dialog.output("reset");
	return key;
}
