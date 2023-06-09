void WLSearchCore(int lth, int NOL, const std::string s, const int index, const std::string colorCommand = "<grn-blk>") {
    const std::string searchInfo = colorCommand + "("
                                   + toString(lth) + "/" + toString(NOL) + "/" + toString(index) + " "
                                   + s.substr(0, lth) + ")";
    bsvLine(searchInfo.c_str());

    const std::string searchResult = WLChinese(lth, index, definitionsColors[0]);

    if (bsvLineGetPlainText(searchResult.c_str()).length() > prerequisites::ScreenX) {
        const int maxDefsPerLine = 6;
        std::vector<std::string> resultLines = {};
        std::string tempLine = "", resultLine = "";
        for (int i = 0, nDefs = 0; i < searchResult.length(); ++i) {
            tempLine.append(1, searchResult[i]);
            if ((i > 0 && searchResult.substr(i, 2) == ")<" && tempLine.find("@") != std::string::npos) || i == searchResult.length() - 1) {
                ++ nDefs;
                resultLine += tempLine;
                tempLine = "";
            }
            if (resultLine.length() && nDefs % maxDefsPerLine == 0 || i == searchResult.length() - 1) {
                resultLines.push_back(resultLine);
                resultLine = "";
            }
        }
        for (int i = 0; i < resultLines.size(); ++i) {
//            printf("\n%d \"%s\"", i, resultLines[i].c_str());
            if (i > 0) {
                printf("\n");
                std::cout << setfill(' ') << std::left << std::setw(bsvLineGetPlainText(searchInfo.c_str()).length()) << "" << " ";
            }
            bsvLine(resultLines[i].c_str());
        }
    } else {
        bsvLine(searchResult.c_str());
    }

    WLHistory.RecordAnswer(s.substr(0, lth), 1);
}
