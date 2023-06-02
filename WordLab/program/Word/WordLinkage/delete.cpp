char WordDelete(const string word) {
	const int lth = word.length(), n = Search(word.c_str(), lth, false);
    char ch = 0;
	Dialog.output("start");
	if (n == 0) {
		Dialog.output("Can not find \"" + word + "\".");
		goto end;
	}
	Dialog.output("Delete " + word + "?");
    ch = getch();
	if (ch == 13 || ch == 10) {
		if(!User.login()) {
            return 0;
        }
		char route[64];
		bool flagEN=0,flagCH=0;
		if (DeleteLine(LibraryRoute(lth,EN),n,1)==0) {
            flagEN = 1;
        }
		if (DeleteLine(LibraryRoute(lth,CH),n,1)==0) {
            flagCH = 1;
        }
		if (!flagEN&&!flagCH) {
            Dialog.output("can not delete ("+word+")!");
        } else if(!flagEN) {
            Dialog.output("can not delete ("+word+") from database ENGLISH!");
        } else if(!flagCH) {
            Dialog.output("can not delete ("+word+") from database CHINESE!");
        } else {
            Dialog.output("("+word+") has been deleted.");
        }
	} else {
        Dialog.output("Cancelled.");
    }
	end:
	const char returnKey = getch();
	Dialog.output("reset");
    return returnKey;
}
