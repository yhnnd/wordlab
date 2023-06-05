void tablerow::printRow(const int x, const int y, const uint colMax) {

    recordColor(prevColor, "printRow");

    const uint columnMax = std::min(tableRowConfigs.colMax, colMax);

    std::vector<std::string> cols {}, vars {};

    for (int c = 0; c < columnMax; ++c) {
        const std::string s = this->col[c];
        if (s.empty() == false) {
            if (s.find("$") == 0) {
                vars.push_back(s);
            } else {
                cols.push_back(s);
            }
        }
    }

	for (int c = 0; c < columnMax; c++) {
        const int colWidth = tableRowConfigs.colMaxWidth * (1 + (c == 0));
        const int left = x + (c == 0 ? 0 : (c + 1) * colWidth);
        clearline(left, y, colWidth, ' ');
        if (c < cols.size()) {
            setForegroundColorAndBackgroundColor("blk-", "-#gry");
            printf(" ");
            setColorByCommand(prevColor, "printRow");
            printf("%s", cols[c].substr(0, colWidth * 2).c_str());
        }
	}

    for (int c = 0; c < vars.size(); ++c) {
        const int colWidth = tableRowConfigs.colMaxWidth;
        const int left = x + (colMax + c) * colWidth;
        clearline(left, y, colWidth, ' ');
        setForegroundColorAndBackgroundColor("blk-", "-#gry");
        printf(" ");
        setForegroundColorAndBackgroundColor("#blu-", "-gry");
        printf("$");
        setColorByCommand(prevColor, "printRow");
        printf("%s", vars[c].substr(1).c_str());
    }
}
