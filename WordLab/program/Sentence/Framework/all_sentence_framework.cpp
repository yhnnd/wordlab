void sts::banner() {
    int x = 0;
    colorset(lightwhite);
    clearScreen();
    colorset(lightgreen);
    gotoxy(x,0);
    cout<<"+----------------------------------+";
    gotoxy(x,1);
    cout<<"|                                  |";
    gotoxy(x,2);
    cout<<"|   Sentence Translating System    |";
    gotoxy(x,3);
    cout<<"|                                  |";
    gotoxy(x,4);
    cout<<"+----------------------------------+";
    gotoxy(0,5);
}


void sts::copySentence(word * wordsDst, const word * wordsSrc, const int numOfWords) {
    for (int r = 0; r <= numOfWords; ++r) {
            strcpy(wordsDst[r].txt, wordsSrc[r].txt);
    }
}


void sts::printSentence(const word * words, const int numOfWords, const struct consoleColor color,
        const char * mode,
        const std::map<int, string> stops) {
    bool showWordNumber = false;
    bool showStops = false;
    bool isInputting = false;

    if (mode != nullptr && strlen(mode)) {
        showWordNumber = strindex(mode, show_word_number) >= 0;
        showStops = strindex(mode, show_stops) >= 0;
        isInputting = strindex(mode, is_inputting) >= 0;
    }

    string stopName = "";

    colorrecord(colorPrev);

    for (int i = 0; i < numOfWords; ++i) {
        if (showStops) {
            // Print Stops.
            if (showWordNumber) {
                setForegroundColorAndBackgroundColor("#gry-", "-blk");
                printf("%d", i);
                setForegroundColorAndBackgroundColor(color.foregroundColor, color.backgroundColor);
            }

            const auto cursor = stops.find(i);
            stopName = "";
            if (cursor != stops.end()) {
                stopName = cursor->second;
            }
            const int wordLth = strlen(words[i].txt);
            // Print whitespaces and stopName(if stopName is available).
            for (int j = 0; j < wordLth; ++j) {
                if (stopName.length() && j == 0) {
                    // Print StopName for current word.
                    if (wordLth < stopName.length()) {
                        // Super Short Word.
                        stopName.erase(wordLth);
                    }
                    printf("%s", stopName.c_str());
                    j = stopName.length() - 1;
                    stopName = "";
                    continue;
                } else {
                    // No StopName for current word.
                    putc(' ', stdout);
                }
            }
            if (i != numOfWords - 1) {
                // If current word is not the last word.
                // Print a whitespace to for separating words.
                putc(' ', stdout);
            }
        } else {
            // If Not Print Stops, Print Sentence .
            if (showWordNumber) {
                setForegroundColorAndBackgroundColor("blk-", "-wte");
                printf("%d", i);
                setForegroundColorAndBackgroundColor(color.foregroundColor, color.backgroundColor);
            }

            // Print Word.
            setForegroundColorAndBackgroundColor(color.foregroundColor, color.backgroundColor);
            printf("%s", words[i].txt);


            if (i + 1 < numOfWords) {
                // If current word is not the last word.
                if ( isInputting == false ||  ispunct(this->punct) == false || i + 2 < numOfWords ) {
                    // Print a whitespace to for separating words.
//                    setForegroundColorAndBackgroundColor("blk-", "-#gry");
                    printf(" ");
                }
            }
        }
    }
    if (ispunct(this->punct)) {
//        setForegroundColorAndBackgroundColor("blk-", "-wte");
        printf("%c", this->punct);
    }

//    printf("            punct is = %d '%c'", this->punct, this->punct);

    colorreset(colorPrev);
}


// width = ScreenX - 1, height = 16.
int sts::FrameworkCore(int x, int y, const int width, const int height) {
    recordxy(pos);
    // Backup Sentence.
    const unsigned int numOfWords = this->rwin + 1;
    this->copySentence(this->sOriginal, this->s, numOfWords);

    if (numOfWords > 1 && this->configs.rearrange_words_order.enabled) {
        WordsOrderFramework();
    }

    {
        colorrecord(colorPrev);
        setForegroundColorAndBackgroundColor("wte-", "-#gry");
        clearscreen(0, 6, width, height);
        colorreset(colorPrev);
    }

    gotoxy(x, y + 1);

    if (this->configs.show_debug_message) {
        cout << endl << "Executing Words Out" << endl;
    }

    this->wordGroups.clear();
    WordsOut();

    if (this->configs.show_debug_message) {
        printf("\nWords Out Done\n");
        printf("\noriginal sentence: ");
        this->printSentence(this->sOriginal, numOfWords, {"#blu-", "-wte"});
        printf("\nmodified sentence: ");
        this->printSentence(this->sModified, this->rwout, {"#red-", "-ylw"});
    }


    // Generate Summary
    const int cols = 6, cw[cols] = {5, 13, 13, 10 ,10, 16};
    int tw = 2 * (cols - 1);
    for (int i = 0; i < cols; ++i) {
        tw += cw[i];
    }
    _table t;
    t.clear();
    t.setrowborder(tw + 1);
    t.setrow(tw,"Summary").setrowborder();
    t.setrow(cols);
    t.setcol(cw[0], "#");
    t.setcol(cw[1],"before");
    t.setcol(cw[2],"after");
    t.setcol(cw[3],"trimmed");
    t.setcol(cw[4],"affix");
    t.setcol(cw[5],"definition");
    t.setrowborder();
    for (int i = 0; i < numOfWords; ++i) {
        t.setrow(cols);
        t.setcol(toString(i));// #
        t.setcol(string("\"") + this->s[i].txt + "\"");// words before.
        t.setcol(string("\"") + this->sModified[i].txt + "\"");// words after.
        t.setcol("trimmed");// Status
        t.setcol("affix");// Times
        t.setcol("def");// Result
    }
    t.setrowborder();
    t.setrow(2).setcol(cw[0]+cw[1]+2, "punctuation").setcol(tw-cw[0]-cw[1]-4,'\''+toString(this->punct)+'\'').setrowborder();
    t.setcolborder('|');

    if (this->configs.show_table_summary) {
        t.printtable(0,9);
    }

    if (this->configs.show_debug_message) {
        printf("\nPrint Sentence Translation\n");
        setForegroundColorAndBackgroundColor("blk-", "-grn");
        printf("Translation");
        setForegroundColorAndBackgroundColor("wte-", "-blk");
        fputc(' ', stdout);
    }

    PrintSentenceTranslation();

//    if (show_debug_message) {
//        cout << endl << "All Done" << endl;
//    }

    // Restore Sentence.
    this->copySentence(this->s, this->sOriginal, numOfWords);
    resetxy(pos);

    return numOfWords;
}


char sts::Input(const COORD inputPos, const COORD indexPos, const COORD translationPos) {
    int r = 0;

    const COORD indicatorPos = {static_cast<short>(inputPos.X + 40), static_cast<short>(inputPos.Y - 1)};

    auto applyInput = [&] (const char mode, const char inputChar) {
        strclr(s[rwin].txt, r);

        colorrecord( colorPrev );

        gotoxy(indicatorPos);
        if (mode == 'i') {
            printf("%-16s", "inputting..");
            if (isalpha(inputChar)) {
                // Print Input Suggestions
                indexCore(s[rwin].txt, indexPos.X, indexPos.Y, green);
            }
        }
        if (mode == 't' || (mode == 'i' && (inputChar == KEY_DELETE || inputChar == MAC_OS_KEY_DELETE))) {
            if (ispunct(inputChar)) {
                this->punct = inputChar;
            }
            printf("%-16s", "translating..");
            // Print Translation
            FrameworkCore(translationPos.X, translationPos.Y, ScreenX - 1, 1);
        }

        // Print Input Sentence.
        gotoxy(inputPos);
//        colorset(lightgreen);
        setForegroundColorAndBackgroundColor("grn-", "-blk");
        clearline(inputPos.X, inputPos.Y, ScreenX - inputPos.X - 1);
        this->printSentence(this->s, this->rwin + 1, {"grn-", "-blk"}, is_inputting);

//        Print Cursor.
        setForegroundColorAndBackgroundColor("#wte-", "-#wte");
        printf(" ");

        colorreset(colorPrev);
    };

    char c = 0;
    for (r = 0, c = 0, strclr(s[rwin].txt); ; ) {
        applyInput('i', c);

        gotoxy(indicatorPos);
        printf("%-16s", "listening");
        fflush(stdin);
        c = getch();

        if (c == KEY_DELETE || c == MAC_OS_KEY_DELETE) {
            c = 0;
            punct = 0;
            if( r > 0 ) {
                s[rwin].txt[--r] = 0;
            } else {
                // r == 0
                strclr(s[rwin].txt);
                if (rwin) {
                    r = strlen(s[--rwin].txt);
                } else {
                    break;
                }
            }
            continue;
        } else if(c=='#'||c=='@') {
            WordSortSelect(s[rwin]);
            continue;
        } else if(c==' '||c==','||c==';'||c=='.'||c=='?'||c=='!'||c == 13||c == 10||c == 0) {
            break;
        } else if (isalpha(c) || isdigit(c) || ispunct(c)) {
            s[rwin].txt[r] = c;
        }

        r++;
    }

    applyInput('t', c);

    if (c==','||c==';'||c=='.'||c=='?'||c=='!'||c == 13||c == 10||c == 0) {
        return c;
    } else {
        return ' ';
    }
}


void sts::Framework() {
    const COORD pos = {0, 5};
    const bool Askprev = _Ask;
    _Ask = false;
    for(;;) {
        reset(false);
        colorset(lightwhite);
        clearScreen();
        banner();
        for (rwin = 0; ; rwin++) {
            punct = Input(pos, {12, 8}, pos);
            if (punct == 0 || punct == KEY_DELETE || punct == MAC_OS_KEY_DELETE || punct == KEY_ESC) {
                if (this->rwin == 0 && strlen(this->s[this->rwin].txt) == 0) {
                    break;
                }
            } else if (punct == 13 || punct == 10) {
                break;
            }
        }
        const char c = popup("Press [ESC] or [BACKSPACE] to exit.", -1);
        if (c == 8 /* backspace */|| c == 127 /* delete */|| c == 27 /* escape */) {
            break;
        }
    }
    _Ask = Askprev;
}


int sts::InputDebugTerm() {
    int r;
    for (r = 0, punct = 0; s[rwin].txt[r] != 0; r++) {
        if (isalpha(s[rwin].txt[r]) || s[rwin].txt[r] == '\'') {
        } else {
            punct = s[rwin].txt[r];
            s[rwin].txt[r] = 0;
            break;
        }
    }
    return punct;
}


void sts::InputDebug() {
    for (rwin = 0; rwin < MAXIMUM; ++rwin) {
        cin >> s[rwin].txt;
//        cout << endl << "InputDebugTerm() = " << InputDebugTerm() << endl;
        if ((punct = InputDebugTerm()) != 0) {
            break;
        }
    }
}


bool sts::DebugSettings() {
    char msgs[][LINEMAX] = {
            {" <wte-gry>(configuration"},
            {" <wte-gry>([1] show debug message"},
            {" <wte-gry>([2] show summary table"},
            {" <#red-ylw>([3.1] enable rearrange words order"},
            {" <wte-gry>([3.2] rearrange words order man set checkers"},
            {" <wte-gry>([3.3] rearrange words order man change words order ask"},
            {" <wte-gry>([3.4] rearrange words order man change words order show"},
            {" <wte-#grn>([4] word translating man select definition"},
            {" <blk-red>(quit"},
            {" <wte-gry>(done"}
    };
    const int max = sizeof(msgs) / sizeof(msgs[0]);
    const int x = 12, y = 0, width = 60, numOfToggles = max - 3;
    bool background = MessageWindow.SetBackground(true);
    bool monochrome = MessageWindow.SetMonochrome(true);

    MessageWindow.Show(x,y,width,&msgs[0][0],max,LINEMAX);

    bool Continue = true;
    int r = 0, rprev = 0;

    for(;; rprev = r) {
        toggles::showAll (
                x, y, width, false, numOfToggles,
                this->configs.show_debug_message,
                this->configs.show_table_summary,
                this->configs.rearrange_words_order.enabled,
                this->configs.rearrange_words_order.manually_set_checkers,
                this->configs.rearrange_words_order.manually_change_words_order_ask,
                this->configs.rearrange_words_order.manually_change_words_order_show,
                this->configs.word_translation.manually_select_definition
        );
        r = MessageWindow.Switch(x, y, width, &msgs[0][0], max, LINEMAX, rprev);
        if (r <= 0 || r == numOfToggles + 1/* quit */) {
            Continue = false;
            break;
        } else if ( r == numOfToggles + 2/* done */) {
            Continue = true;
            break;
        } else if (r > numOfToggles + 2) {
            popup(" DebugSettings: [Error] choice = ", toString(r), -1);
        } else {
            toggles::toggle (
                    x, y, width, false, r, numOfToggles,
                    &(this->configs.show_debug_message),
                    &(this->configs.show_table_summary),
                    &(this->configs.rearrange_words_order.enabled),
                    &(this->configs.rearrange_words_order.manually_set_checkers),
                    &(this->configs.rearrange_words_order.manually_change_words_order_ask),
                    &(this->configs.rearrange_words_order.manually_change_words_order_show),
                    &(this->configs.word_translation.manually_select_definition)
            );
        }
    }
    MessageWindow.Hide(x,y,width,max,LINEMAX);
    MessageWindow.SetBackground(background);
    MessageWindow.SetMonochrome(monochrome);
    return Continue;
}


void sts::FrameworkDebug() {
    int x = 0, y = 5;

    this->reset(true);

    if (DebugSettings() == false) {
        return;
    }

    bool AskCharPrev = _Ask;
    bool ShowMsgPrev = _Show;

    for(;;) {
        _Ask = this->configs.rearrange_words_order.manually_change_words_order_ask;
        _Show = this->configs.rearrange_words_order.manually_change_words_order_show;

        colorset(lightwhite);
        clearScreen();

        banner();

        memset(this->s, 0, sizeof(s));
        memset(this->sOriginal, 0, sizeof(s));
        memset(this->sModified, 0, sizeof(s));

        InputDebug();

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        fflush(stdin);

        const int result = FrameworkCore(x, y, ScreenX - 1, 16);
        if (result == 0) {
            break;
        }

        const char ch = popup("Press [ESC] or [BACKSPACE] to exit", -1);
        if (ch == KEY_CARRIAGE_RETURN || ch == KEY_NEW_LINE) {
            continue;
        } else if (ch == 8 /* backspace */|| ch == 127 /* delete */|| ch == KEY_ESC /* escape */) {
            break;
        }
    }
    _Ask = AskCharPrev;
    _Show = ShowMsgPrev;
}
