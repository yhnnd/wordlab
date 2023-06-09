char addPhrase(const string s, const enum AddMode mode) {
	if (s.empty()) {
        return 0;
    }

	Dialog.output("start");

    if (mode == AddMode::AddPhrase) {
        Dialog.output("add phrase \"" + s + "\" ?");
    } else if (mode == AddMode::RedirectPhrase) {
        Dialog.output("redirect phrase \"" + s + "\" ?");
    } else {
        return 0;
    }

    const char ch = getch();

	if (ch != 13 && ch != 10) {
		popup("cancelled", -1);
	} else {
        addPhraseCore(s, mode);
    }

    const char key = getch();
    Dialog.output("reset");
    return key;
}
