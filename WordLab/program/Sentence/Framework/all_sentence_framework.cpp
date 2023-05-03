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


void sts::printSentence(const word * words, const int numOfWords, const struct consoleColor color) {
    colorrecord(colorPrev);
    setForegroundColorAndBackgroundColor(color.foregroundColor, color.backgroundColor);
    for (int i = 0; i < numOfWords; ++i) {
        printf("%s ", words[i].txt);
    }
    if (ispunct(this->punct)) {
        printf("%c", this->punct);
    }
    colorreset(colorPrev);
}


void sts::FrameworkCore(int x, int y) {
    recordxy(pos);
    // Backup Sentence.
    const unsigned int numOfWords = this->rwin + 1;
    this->copySentence(this->sOriginal, this->s, numOfWords);

    if (rearrange_words_order) {
        WordsOrderFramework();
    }

    {
        colorrecord(colorPrev);
        setForegroundColorAndBackgroundColor("wte-", "-#gry");
        clearscreen(0, 6, ScreenX - 1, 16);
        colorreset(colorPrev);
    }

    gotoxy(x, y + 1);

    if (show_debug_message) {
        cout << endl << "Executing Words Out" << endl;
    }

    this->wordGroups.clear();
    WordsOut();

    if (show_debug_message) {
        cout << endl << "Words Out Done" << endl;
        this->printSentence(this->sOriginal, numOfWords, {"#blu-", "-wte"});
        cout << endl;
        this->printSentence(this->sModified, this->rwout, {"#red-", "-ylw"});
        cout << endl << "Print Sentence Translation" << endl;
    }

    PrintSentenceTranslation();

    if (show_debug_message) {
        cout << endl << "All Done" << endl;
    }

    // Restore Sentence.
    this->copySentence(this->s, this->sOriginal, numOfWords);
    resetxy(pos);
}


char sts::Input(int x,int y) {
    int r;
    char c;
    for(r=0,c=0,strclr(s[rwin].txt);; r++) {
        begin:
        colorset(lightwhite);
        c = getche();
        if(c==8) {
            cout<<" \b";
            c = 0;
            punct = 0;
            if( r > 0 ) {
                s[rwin].txt[--r]=0;
            } else if(rwin) {
                strclr(s[rwin].txt);
                r = strlen(s[--rwin].txt);
                FrameworkCore(x,y);
            } else {
                break;
            }
            indexCore(s[rwin].txt,12,8,green);
            goto begin;
        } else if(c=='#'||c=='@') {
            cout<<"\b";
            WordSortSelect(s[rwin]);
            r--;
        } else if(c==' '||c==','||c==';'||c=='.'||c=='?'||c=='!'||c == 13||c == 10||c == 0) {
            break;
        } else if( c > 0 ) {
            s[rwin].txt[r] = c;
        }
        indexCore(s[rwin].txt,12,8,green);
    }
    strclr(s[rwin].txt,r);
    if (c==','||c==';'||c=='.'||c=='?'||c=='!'||c == 13||c == 10||c == 0) {
        return c;
    } else {
        return ' ';
    }
}


void sts::Framework() {
    int x = 0, y = 5;
    const bool Askprev = _Ask;
    _Ask = false;
    for(;;) {
        reset();
        colorset(lightwhite);
        clearScreen();
        banner();
        for (rwin = 0; ; rwin++) {
            punct = Input(x, y);
            if (punct == 0) {
                break;
            } else if (punct == 13) {
                break;
            }
            FrameworkCore(x, y);
        }
        if (punct == 0) {
            break;
        }
        const char c = popup("Press [ESC] to exit", -1);
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
    bool Continue = true;
    int x = 20, y = 0, width = 40, r = 0, rprev = 0, total = 3;
    char msgs[][LINEMAX] = {
            "<-gry>(configuration",
            "<-gry>(show debug information",
            "<-gry>(translate automatically",
            "<-gry>(rearrange words order",
            "<-gry>(done"
    };
    int max = sizeof(msgs) / sizeof(msgs[0]);
    bool background = MessageWindow.SetBackground(true);
    bool monochrome = MessageWindow.SetMonochrome(true);
    MessageWindow.Show(x,y,width,&msgs[0][0],max,LINEMAX);
    for(;; rprev=r) {
        togglesShow(x,y,width,false,total,show_debug_message,auto_word_translation,rearrange_words_order);
        r = MessageWindow.Switch(x,y,width,&msgs[0][0],max,LINEMAX,rprev);
        toggles(x,y,width,false,r,total,&show_debug_message,&auto_word_translation,&rearrange_words_order);
        if ( r <= 0 ) {// quit
            Continue = false;
            break;
        } else if( r >= max-1 ) {
            Continue = true;
            break;
        }
    }
    MessageWindow.Hide(x,y,width,max,LINEMAX);
    MessageWindow.SetBackground(background);
    MessageWindow.SetMonochrome(monochrome);
    return Continue;
}


void sts::FrameworkDebug() {
    int x = 0, y = 5;

    reset_debug();

    if (DebugSettings() == false) {
        return;
    }

    bool AskCharPrev = _Ask;
    bool ShowMsgPrev = _Show;

    for(;;) {
        _Ask = show_debug_message;
        _Show = show_debug_message;

        colorset(lightwhite);
        clearScreen();

        banner();

        memset(this->s, 0, sizeof(s));
        memset(this->sOriginal, 0, sizeof(s));
        memset(this->sModified, 0, sizeof(s));

        InputDebug();

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        fflush(stdin);

        if (this->rwin > 0) {
            FrameworkCore(x, y);
        }

        const char ch = popup("Press [ESC] to exit", -1);
        if (ch == KEY_CARRIAGE_RETURN || ch == KEY_NEW_LINE) {
            continue;
        } else if (ch == KEY_ESC) {
            break;
        }
    }
    _Ask = AskCharPrev;
    _Show = ShowMsgPrev;
}
