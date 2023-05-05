string AddWordGetSort() {
	string msg = AddWordSortSelect(getxy().X, getxy().Y);
	if(msg.length()) {
        AddWordPrintMessage(7,msg);
    } else {
        AddWordPrintErrorMessage(6);
    }
	return msg;
}
