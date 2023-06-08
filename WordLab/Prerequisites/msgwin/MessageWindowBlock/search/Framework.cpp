int messageBlocks::Search (const char what[][LINEMAX], const int N) {
	int n = 0, nPrev = N, lth = 30;
	char c;
    std::string keyword = "";

	recordColor(colorprev, "Search");

    setColor(bothlightwhite, "Search");
	clearline(x + (width - lth) / 2, y - 1, lth);

	for (; (c = getch()) != 13 && c != 10; nPrev = n) {
		if (c == 8 || c == 127) {
            if (keyword.empty()) {
                n = 0;
                goto end;
            }
            keyword.pop_back();
		} else {
			keyword.push_back(c);
		}
		if (keyword.length() > lth) {
			n = 0;
			goto end;
		}
		n = SearchCore(what, max, keyword);

        setColor(((n > 0 && n < max) ? backlightgreen : (keyword.length() < lth / 2) ? backlightyellow : backlightred), "Search");
		clearline(x + (width - lth) / 2, y - 1, lth);
		printf("%s", keyword.c_str());

		if (keyword.back() == '=') {
			keyword.pop_back();
            resetColor(colorprev, "Search");
			if (keyword == "tips()") {
                setForegroundColorAndBackgroundColor("wte-", "-#gry");
                clearline(x + (width - lth) / 2, y - 1, lth);
            }
            launch(keyword);
		} else {
            FillAll(what, nPrev, n, max);
        }
	}
end:
    resetColor(colorprev, "Search");
	clearline(x + (width - lth) / 2, y - 1, lth);
	return n;
}
