int WLSearchPhrase(const char *msg) {
	int n = 1, lineNo = 0;
	string s = string(",") + msg + ",";
    string line = "";
	for (auto it = s.begin(); it != s.end(); ++it) {
		if (*it == ' ') {
            ++n;
            *it = ',';
		}
	}

	const string route = PhraseRouteA + toString(n) + PhraseRouteB;
	ifstream fin(route);

    if (fin) {
        while (std::getline(fin, line)) {
            ++lineNo;
            if (line.find(s) == 0) {
                const string defs = line.erase(line.find_last_not_of(";") + 1).substr(s.length());
                colorrecord(colorPrev);
                const int BeginY = 5;
                clearscreen(0, BeginY, ScreenX, ScreenY - 1 - BeginY);
                setForegroundColorAndBackgroundColor("wte-", "-#gry");
                clearscreen(0, 3, ScreenX - 1, 8);

                gotoxy(0, BeginY);
                setForegroundColorAndBackgroundColor("grn-", "-blk");
                printf(" %d / %d \"%s\" ", n, lineNo, msg);
                setForegroundColorAndBackgroundColor("ylw-", "-blk");
                printf("\"%s\"\n", defs.c_str());

                colorreset(colorPrev);
                fin.close();
                return lineNo;
            }
        }
        fin.close();
        return 0;
    } else {
        popup(set_mode_y_is_constant);
        popup("#offsetY=0;");
        popup("cannot open file \"", route, "\"", 0);
        return -1;
    }
}
