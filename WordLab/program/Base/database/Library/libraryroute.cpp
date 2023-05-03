string LibraryRoute(int lth,lang LANG){
	string s;
	if (LANG == lang::EN) {
        s = englishroute;
    } else if(LANG == lang::CH) {
        s = chineseroute;
    } else {
        popup("library route: unknown language ",toString(LANG),0);
    }
	s += toString(lth);
	s += ".csv";
	return s;
}
