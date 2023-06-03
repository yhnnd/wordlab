struct phraseSearchResult getPhraseDefinitions(const int phraseLth, const std::vector<std::string> phrase) {

    const std::string route = PhraseRouteA + toString(phraseLth) + PhraseRouteB;
    ifstream fin(route);

    struct phraseSearchResult result;

    if (fin) {
        result.phrase = phrase;
        result.phraseLth = phraseLth;
        result.phrase = phrase;
        result.lineNo = 0;

        const std::string searchKey = "," + join(phrase, ",") + ",";

//        printf ("phraseLth = %d, phrase = \"%s\"\n", phraseLth, searchKey.c_str());
//        getch();

        std::string line = "";

        while (std::getline(fin, line)) {
            ++ result.lineNo;
            if (line.find(searchKey) == 0) {
                fin.close();
                result.status = phraseSearchResultStatus::succeeded;
                result.defsLine = line;
                result.defs = line.erase(line.find_last_not_of(";") + 1).substr(searchKey.length());
                result.defsVector = split(result.defs, ";");
                return result;
            }
        }

        fin.close();
        result.status = phraseSearchResultStatus::failed;
        return result;
    } else {
        result.status = phraseSearchResultStatus::failed;
        result.message = "cannot open file \"" + route + "\"";
        return result;
    }
}


struct phraseSearchResult getPhraseDefinitions(const std::string msg) {
    if (msg.find(" ") != std::string::npos) {
        std::vector<std::string> phrase = split(msg, " ");
        return getPhraseDefinitions(phrase.size(), phrase);
    } else if (msg.find(",") != std::string::npos) {
        std::vector<std::string> phrase = split(msg, ",");
        return getPhraseDefinitions(phrase.size(), phrase);
    } else {
        struct phraseSearchResult result;
        result.status = phraseSearchResultStatus::failed;
        result.message = "search failed. invalid phrase";
        return result;
    }
}


int WLSearchPhrase(const char *msg) {

    const struct phraseSearchResult result = getPhraseDefinitions(msg);

    if (result.status == phraseSearchResultStatus::succeeded) {

        const int BeginY = 5;

        colorrecord(colorPrev);

        clearscreen(0, BeginY, ScreenX, ScreenY - 1 - BeginY);
        setForegroundColorAndBackgroundColor("wte-", "-#gry");
        clearscreen(0, 3, ScreenX - 1, 8);

        gotoxy(0, BeginY);
        setForegroundColorAndBackgroundColor("grn-", "-blk");
        printf(" %d / %d \"%s\" ", result.phraseLth, result.lineNo, msg);
        setForegroundColorAndBackgroundColor("ylw-", "-blk");

        for (const std::string & defItem: result.defsVector) {
            printf(" \"%s\"", defItem.c_str());
        }
        printf("\n");

        colorreset(colorPrev);

        return result.lineNo;
    } else if (result.message.empty() == true) {
        return 0;
    } else {
        popup(set_mode_y_is_constant);
        popup("#offsetY=0;");
        popup(result.message, 0);
        return -1;
    }
}
