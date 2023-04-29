int WLFrameworkCore(string s) {
	int n = 0, ReturnLetter = 0;
	string s2(s);
	WLHistory.RecordSearch(s,0);
	if (BL) {
        n = WLSearch(s,0);//UPPER-LOWER CASE SENSITIVE
    }
	if (BL && n == 0) {
        n = WLSearch(s,1);//UPPER_LOWER CASE IGNORED
    }
    printf("search result is %d\n", n);
	if (BL && n == 0) {
        n = WLSearchFuzzy(s.c_str(),1);
    }
	if (DL) {
        printf("\nprefix n = %d, s2= %s\n", n, s2.c_str());
        prefix(s2);
    }
	if (SL) {
        printf("\nWLSearchSimilarSpelling s = %s\n", s.c_str());
        WLSearchSimilarSpelling(s,2);
    }
	if (CL && n == 0) {
        printf("\nAddNew s = %s\n", s.c_str());
		AddNew(s);
		ReturnLetter = 13;
	}
    printf("\nWLFrameworkCore returns %d\n", ReturnLetter);
	return ReturnLetter;
}
