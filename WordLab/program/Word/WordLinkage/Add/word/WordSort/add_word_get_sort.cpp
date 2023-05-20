string AddWordGetSort(const int x, const int y, const int width) {
	string msg = AddWordSortSelect(x, y, width);
	if(msg.length()) {
        AddWordPrintMessage(7, msg);
    } else {
        AddWordPrintErrorMessage(6);
    }
	return msg;
}
