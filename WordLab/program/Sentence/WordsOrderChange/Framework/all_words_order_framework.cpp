void sts::WordsOrderFindMain() {
    int r, r0, r1;
    FindMain:
    for(r=0,r0=-1; r<=rwin; r++) {
        if(wordSortIncludes(s[r].txt, {1})) {
            r0=r;    //n.
            break;
        }
    }
    for(r=0,r1=-1; r<=rwin; r++) {
        if(wordSortIncludes(s[r].txt, {8})) {
            r1=r;    //pron.
            break;
        }
    }
    for(;;) {
        if (r0 >= 0) {
            const char ch = AskChar(s[r0].txt, " is the Main?");
            if (ch == 13 || ch == 10) {
                TheMain = r0;    //n.
                break;
            }
        }
        if (r1 >= 0) {
            const char ch = AskChar(s[r1].txt," is the Main?");
            if (ch == 13 || ch == 10) {
                TheMain = r1;    //pron.
                break;
            }
        }
        for (r=0; r<=rwin; r++) {
            const char ch = AskChar(s[r].txt," is the Main?");
            if (ch == 13 || ch == 10) {
                TheMain = r;    //custom
                break;
            }
        }
        break;
    }
    if (TheMain<0||TheMain>rwin) {
        goto FindMain;
    }
}
// S.T.S. Words Order - find Main
//Since   2014/6/18
//Updated 2014/6/18 17:53

void sts::WordsOrderFrameworkCore(const int n,vector<int> ListPos) {
    switch(ListPos[n]) {
        case 0:
            ClauseCheck();
            break;
        case 1:
            ConjCheck();
            break;
        case 2:
            SpecialWordSpot1Question();
            break;
        case 3:
            WordsOrderChange1();
            break;
        case 4:
            SpecialWordSpot2Preposition();
            break;
        case 5:
            SpecialWordSpot3AdverbialClause();
            break;
        default:
            break;
    }
}

void sts::WordsOrderSettings(vector<int> & ListPos,vector<string> & CheckerInfo) {
    COORD pos = getxy();
    for(int r = 0; r < CheckerMax; r++ ) {
        popup("#time=reset();");
        popup(setModeYIsConstant);
        popup("第",toString(r+1),"步放置的工具爲?",0);
        MessageWindow.Frame(0,2,16,30,CheckerInfo);
        ListPos[r] = MessageWindow.Switch(2,16,30,CheckerInfo,ListPos[r>0?r-1:0]+1) - 1;
    }
    gotoxy(pos);
}

