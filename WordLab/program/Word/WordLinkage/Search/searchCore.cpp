void WLSearchCore(int lth, int NOL, string s, int k, string colorcmdlabel="<grn->") {
	string search_result = colorcmdlabel + "("
            + tostring(lth) + "/" + tostring(NOL) + "/" + tostring(k) + " "
            + s.substr(0,lth) + ")";
	search_result += WLchinese(lth, k, CLRL[0]);
	WLHistory.RecordAnswer(s.substr(0,lth),1);
//	cout<<search_result.c_str()<<endl;
//    gotoxy(0, 4);
	bsvline(search_result.c_str());
}
