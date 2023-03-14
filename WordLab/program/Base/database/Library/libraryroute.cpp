string LibraryRoute(int lth,lang LANG){
	string s;
	if(LANG == lang::EN) s = englishroute;
	else if(LANG == lang::CH) s = chineseroute;
	else popup("library route: unknown language ",tostring(LANG),0);
	s += tostring(lth);
	s += ".csv";
	return s;
}
