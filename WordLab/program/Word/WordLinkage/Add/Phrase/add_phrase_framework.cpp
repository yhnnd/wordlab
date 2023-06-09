void AddPhrase(const string s) {
	if (s.empty()) {
        return;
    }
	Dialog.output("start");
	Dialog.output("add phrase \"" + s + "\" ?");
    const char ch = getch();
	if (ch != 13 && ch != 10) {
		popup("cancelled", -1);
	} else {
        AddPhraseCore(s);
    }
    getch();
    Dialog.output("reset");
}
