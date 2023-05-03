void SearchReverse() {
	string s = "";
	const char tempfilename[]="buf.dat";
    char ch;
	for(;;) {
	    Dialog.output("start");
		Dialog.output("search:", lightgreen);
		cin >> s;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        fflush(stdin);
		remove(tempfilename);
		for (int r = 1; r <= 30; r++) {
            findinfile(s,LibraryRoute(r,lang::CH),tempfilename);
        }
        if (file_filter_comma(tempfilename)) {
            MessageWindow.bsvviewer("buf.dat", 0, 10, 0, ScreenX - 20,ScreenY - 2, false);
            ch = popup("press [ENTER] to continue.", -1);
        } else {
            ch = popup("No Result Found.", -1);
        }
	    if (ch == 13 || ch == 10) {
            continue;
        } else {
            break;
        }
	}
	Dialog.output("reset");
}
