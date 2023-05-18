string AddWordSortSelect(const int x, const int y) {
    static int choice = 1;
    const bool isMonochromePrev = MessageWindow.SetMonochrome(true);
    const int width = 20;
	const vector<string> optionsMenu = {
        "select word sort",
        "set word sort n.",
        "set word sort v.",
        "set word sort adj.",
        "set word sort adv.",
        "<ylw->(set word sort) ",
        "<red->(cancel)"
    };

	MessageWindow.Frame(0, x, y, width, optionsMenu);
	choice = MessageWindow.Switch(x, y, width, optionsMenu, choice);
    MessageWindow.Frame(-1, x, y, width, optionsMenu.size(), 0);

	MessageWindow.SetMonochrome(isMonochromePrev);

	switch (choice) {
	    case 1:  return "n.";   break;
	    case 2:  return "v.";   break;
	    case 3:  return "adj."; break;
	    case 4:  return "adv."; break;
	    case 5:
            char s[16];
            listen(s, 0, 1, {13, 10, 0, EOF}, sizeof(s));
            return s;
            break;
	    default:
            AddWordPrintErrorMessage(5);
            break;
	}
	return "";
}
