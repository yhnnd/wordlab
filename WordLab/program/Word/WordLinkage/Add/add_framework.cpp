char AddNew(const string s) {
	if(s.empty()) {
        return 0;
    }
//    printf("\nadd new begin\n");
	Dialog.output("start");
//    printf("\nprint dialog\n");
	for(int TIMES = 1; TIMES <= 2; TIMES++) {
        if (TIMES == 1) {
            if (s.find(" ") == string::npos) {
                AddWordPrintMessage(1, s);
            } else {
                AddWordPrintMessage(6, s);
            }
        } else if (TIMES == 2) {
            AddWordPrintMessage(2, s);
        } else {
            break;
        }
        // printf("\nwaiting for getch\n");
        const int key = getch();
		if (key != 13 && key != 10) {
			AddWordPrintErrorMessage(1, s);
			goto end;
		}
	}
    // printf("\ncheck user login\n");
	if (CType) {
        if(!User.login()) {
            goto end;
        }
    }
	if (s.find(" ") != std::string::npos) {
//        printf("\nadd new phrase\n");
		popup("Add Phrase", 0);
		AddPhrase(s);
	} else {
//        printf("\nadd new word\n");
		popup("Add word <ylw->(", s, 0);
		AddWord(s);
	}
	end:
	const char key = getch();
	Dialog.output("reset");
	return key;
}
