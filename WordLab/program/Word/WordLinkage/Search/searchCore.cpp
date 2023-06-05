void WLSearchCore(int lth, int NOL, string s, int k, string colorcmdlabel="<grn->") {
	string search_result = colorcmdlabel + "("
            + toString(lth) + "/" + toString(NOL) + "/" + toString(k) + " "
            + s.substr(0,lth) + ")";
	search_result += WLChinese(lth, k, definitionsColors[0]);
	WLHistory.RecordAnswer(s.substr(0,lth),1);
//	cout<<search_result.c_str()<<endl;
//    gotoxy(0, 4);
	bsvLine(search_result.c_str());
}
