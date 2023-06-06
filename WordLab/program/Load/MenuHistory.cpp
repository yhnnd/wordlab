void load::History() {
	const int x = 0, y = 9, width = 30;
    int n = 0, nPrev = 0, times = 0;
	char Menu[20][LINEMAX];
	if (LANGUAGE == lang::EN) {
        loadmsg((char*)Menu, SetHistoryRoute"en.csv", 20, LINEMAX, 1, 1);
    } else if (LANGUAGE == lang::CH) {
        loadmsg((char*)Menu, SetHistoryRoute"ch.csv", 20, LINEMAX, 1, 1);
    }
	for (times = 0; ; nPrev = n, ++times) {
	    n = multitask(x, y, width, Menu, times, nPrev);
		switch (n) {
	        case  1: WLHistory.read(SearchHistory, "SEARCH HISTORY"); break;
	        case  2: WLHistory.read(AnswerHistory, "ANSWER HISTORY"); break;
	        case  3: WLHistory.read(UnknownHistory, "UNKNOWN HISTORY"); break;
	        case  4: WLHistory.clear(); break;
	        default: return; break;
        }
    }
}
