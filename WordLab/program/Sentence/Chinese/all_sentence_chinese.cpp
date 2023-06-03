int sts::TranslationSelectItem(const int ItemMax, const string def_line,
                               const int x, const int y,
                               const int width, const int height) {
    int ItemNumber = 1;
    recordxy(pos);
    clearline(x,y);
    printf("\"%s\"\n", def_line.c_str());
    ItemNumber = MessageWindow.ConfirmSwitch(ItemMax, x, y+1, width, height);
    resetxy(pos);
    return ItemNumber;
}


int sts::TranslationGetItem(const string line, int ItemNumber, char * result, const size_t size) {
    // IF ITEM NOT FOUND THEN RETURN "NULL"
    // ITEM_NUMBER DEFAULT IS 1
    int i = 0, CurrentItemNumber = 0;
    bool InItemTranslation=false, InItemTranslationComment=false;
    for (i = 0, CurrentItemNumber = 0; i < line.length() && CurrentItemNumber < ItemNumber; ++i) {
        if (line[i] == '@') {
            if (InItemTranslation == false) {
                //Begin of Item Translation
                InItemTranslation = true;
                ++CurrentItemNumber;
            } else {
                //End of Item Translation
            }
        }
        if (line[i] == ';') {
            InItemTranslation=false;
        }
    }
    if (i < line.length() && CurrentItemNumber == ItemNumber) { //Item Found
        string defItemText = "";
        for (; i<line.length(); ++i) {
            if (line[i]=='\n'||line[i]==0) {
                break;
            } else if (line[i]=='@'||line[i]==';') {
                break;
            } else if (strchr("([<",line[i])) {
                InItemTranslationComment = true;
            } else if (strchr(")]>",line[i])) {
                InItemTranslationComment = false;
            } else if (InItemTranslationComment == false) {
                defItemText += line[i];
            }
        }
        memset(result, 0, size);
        strncpy(result, defItemText.c_str(), defItemText.length());
        return ItemNumber;
    }
    return 0;
}


int sts::Translation(int lth, int LineNumber, char * result, const size_t size) {
    int NOL = 0;
    string line = "";
    ifstream fin;
    Library(fin,lth,CH);
    if (fin) {
        while(getline(fin,line)) {
            ++NOL;
            if (NOL == LineNumber) { // LINE FOUND
                if (line.find("/redirected./") != string::npos) { // LINE REDIRECTED

                    const std::string result_msg = ChineseRedirect(line, lth, LineNumber);

                    if (result_msg.empty() == true) {
                        // Result Message is Empty.
                        if (lth > 0 && LineNumber > 0) {
                            return Translation(lth, LineNumber, result, size);
                        } else {
                            memset(result, 0, size);
                            strcpy(result, "unknown error");
                            return 0;
                        }
                    } else {
                        // Result Message is not Empty
                        memset(result, 0, size);

                        const std::string indicator_phrase = "PHRASE ";
                        if (result_msg.find(indicator_phrase) == 0) {
                            const std::string target_phrase = result_msg.substr(indicator_phrase.length());
                            phraseSearchResult phResult = getPhraseDefinitions(target_phrase);
                            if (phResult.status == phraseSearchResultStatus::succeeded) {
                                const std::string phraseDefinition = phResult.defsVector[0];
                                strncpy(result, phraseDefinition.c_str(), phraseDefinition.length());
                            } else {
                                strncpy(result, target_phrase.c_str(), target_phrase.length());
                            }
                        } else {
                            strncpy(result, result_msg.c_str(), result_msg.length());
                        }
                        return LineNumber;
                    }
                }
                // IF LINE HAS MULTIPLE ITEMS THEN SELECT ITEM
                int ATail = stroccurtimes(line.c_str(),"@");
                int ItemNumber = 1;
                if ( ATail > 1 && this->configs.word_translation.manually_select_definition == true ) {
                    // SELECT ITEM
                    ItemNumber = TranslationSelectItem(ATail, line, 2, 16, 20, 2);
                }
                fin.close();
                return TranslationGetItem(line.substr(lth), ItemNumber, result, size);
//                break;
            }
        }
    } else {
        errorlog("Translation","cannot connect database",toString(lth));
    }
    fin.close();
    return 0;
}

