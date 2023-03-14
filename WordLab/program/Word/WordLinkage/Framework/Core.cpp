int WLFrameworkCore(string s) {
	int n=0,ReturnLetter=0;
	string s2(s);
	WLHistory.RecordSearch(s,0);
	if(BL)       n = WLSearch(s,0);//UPPER-LOWER CASE SENSITIVE
	if(BL&&n==0) n = WLSearch(s,1);//UPPER_LOWER CASE IGNORED
	if(BL&&n==0) n = WLSearchFuzzy(s.c_str(),1);
	if(DL)       prefix(s2);
	if(SL)       WLSearchSimilarSpelling(s,2);
	if(CL&&n==0) {
		AddNew(s);
		ReturnLetter = 13;
	}
	return ReturnLetter;
}
