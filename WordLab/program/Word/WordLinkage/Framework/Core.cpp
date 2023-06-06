int WLFrameworkCore(const std::string s) {
	int n = 0, ReturnLetter = 0;
	string s2(s);

    recordColor(colorPrev, "WLFrameworkCore");
    setForegroundColorAndBackgroundColor("wte-", "-#gry");
    clearScreen(0, 3, ScreenX - 1, 8);
    resetColor(colorPrev, "WLFrameworkCore");

	WLHistory.RecordSearch(s, 0);

	if (BL) {
        n = WLSearch(s, false, true, 'n', true);//UPPER-LOWER CASE SENSITIVE
    }
	if (BL && n == 0) {
        n = WLSearch(s, true, true, 'n', true);//UPPER_LOWER CASE IGNORED
    }
//    printf("search result is %d\n", n);
	if (BL && n == 0) {
        n = WLSearchFuzzy(s.c_str(),1);
    }
	if (DL) {
//        printf("\nprefix n = %d, s2= %s\n", n, s2.c_str());
        prefix(s2);
    }
	if (SL) {
//        printf("\nWLSearchSimilarSpelling s = %s\n", s.c_str());
        WLSearchSimilarSpelling(s,2);
    }
	if (CL && n == 0) {
//        printf("\nAddNew s = %s\n", s.c_str());
        ReturnLetter = AddNew(s);
	}
//    printf("\nWLFrameworkCore returns %d\n", ReturnLetter);
	return ReturnLetter;
}
