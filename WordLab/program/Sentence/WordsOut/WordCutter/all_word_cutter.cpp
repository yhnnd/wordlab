enum _wordCutterSymbols {
    _prefix_RE = 1,
    _prefix_DIS = 2,
    _postfix_apostrophe_S = 3,
    _postfix_S = 4,
    _postfix_ING = 5,
    _postfix_ED = 6,
    _postfix_LY = 7,
    _postfix_AL = 8,
    _prefix_ANTI = 9,
    _postfix_ER = 10,
    _postfix_OR = 11,
    _postfix_ISM = 12,
    _postfix_IST = 13,
    _prefix_UN = 14,
};

void sts::wordcuttercheck(char *s, int lth, int *n, int *de) {
    if (strindex(s,"re")==0&&lth-2>-1)     {
        *n = _wordCutterSymbols::_prefix_RE;    //re *
        *de = 2;
    } else if(strindex(s,"dis")==0&&lth-3>-1)    {
        *n = _wordCutterSymbols::_prefix_DIS;    //dis *
        *de = 3;
    } else if(strindex(s,"'s")==lth-2&&lth-2>-1) {
        *n = _wordCutterSymbols::_postfix_apostrophe_S;    //'s
        *de = 2;
    } else if(strindex(s,"s")==lth-1&&lth-1>-1)  {
        *n = _wordCutterSymbols::_postfix_S;    //s
        *de = 1;
    } else if(strindex(s,"ing")==lth-3&&lth-3>-1) {
        *n = _wordCutterSymbols::_postfix_ING;    //ing
        *de=3;
    } else if(strindex(s,"ed")==lth-2&&lth-2>-1) {
        *n = _wordCutterSymbols::_postfix_ED;    //ed
        *de = 2;
    } else if(strindex(s,"ly")==lth-2&&lth-2>-1) {
        *n = _wordCutterSymbols::_postfix_LY;    //ly
        *de = 2;
    } else if(strindex(s,"al")==lth-2&&lth-2>-1) {
        *n = _wordCutterSymbols::_postfix_AL;    //al
        *de = 2;
    } else if(strindex(s,"anti")==0&&lth-4>-1)   {
        *n = _wordCutterSymbols::_prefix_ANTI;    //anti *
        *de = 4;
    } else if(strindex(s,"er")==lth-2&&lth-2>-1) {
        *n = _wordCutterSymbols::_postfix_ER;    //er
        *de = 2;
    } else if(strindex(s,"or")==lth-2&&lth-2>-1) {
        *n = _wordCutterSymbols::_postfix_OR;    //or
        *de = 2;
    } else if(strindex(s,"ism")==lth-3&&lth-3>-1) {
        *n = _wordCutterSymbols::_postfix_ISM;    //ism
        *de = 3;
    } else if(strindex(s,"ist")==lth-3&&lth-3>-1) {
        *n = _wordCutterSymbols::_postfix_IST;    //ist
        *de = 3;
    } else if(strindex(s,"un")==0&&lth-2>-1)     {
        *n = _wordCutterSymbols::_prefix_UN;    //un *
        *de = 2;
    }
}


void sts::wordcutterremove(char *s,int n) {
    int r;
    if (n == _wordCutterSymbols::_prefix_RE) {
        for(r=0; s[r+2]; r++) s[r]=s[r+2];    //re *
        strclr(s,r);
    } else if (n == _wordCutterSymbols::_prefix_DIS) {
        for(r=0; s[r+3]; r++) s[r]=s[r+3];    //dis *
        strclr(s,r);
    } else if (n == _wordCutterSymbols::_prefix_ANTI) {
        for(r=0; s[r+4]; r++) s[r]=s[r+4];    //anti *
        strclr(s,r);
    } else if (n == _wordCutterSymbols::_prefix_UN) {
        for(r=0; s[r+2]; r++) s[r]=s[r+2];    //un *
        strclr(s,r);
    }
}


void sts::fileIn(char msg[][LINEMAX],const char *route) {
    int r=0,r1=0;
    char c=0;
    FILE *fp=fopen(route,"r");
    rewind(fp);
    while(true) {
        c=fgetc(fp);
        if(c==';') {
            while(true) {
                c=fgetc(fp);
                if(c=='\n'||c==EOF) break;
            }
        }
        if(c==EOF) {
            strclr(msg[r],r1);
            break;
        }
        if(c=='\n') {
            strclr(msg[r],r1);
            r++;
            r1=0;
        } else msg[r][r1++]=c;
    }
    fclose(fp);
}


bool sts::WordCutter(char *s) {
    int n = 0, de = 0, lth = strlen(s), max = filelines(AffixCutRoute,true);
    char Cut[max][LINEMAX], Add[max][LINEMAX];
    fileIn(Cut,AffixCutRoute);
    fileIn(Add,AffixAddRoute);
    wordcuttercheck(s,lth,&n,&de);
    if (n==0) {
        return false;
    }
    if (AskChar("remove \"", Cut[n], "\"?")==13) {
        wordcutterremove(s,n);
        strclr(s,lth - de);
    } else {
        return false;
    }

    if (n == _postfix_ING) {
        char def [32];
        if (getChineseOfWord(s, def, sizeof(def))) {
            printf("%s", def);
            return true;
        } else {
            char temp [32];
            strcpy(temp, s);
            strcat(s, "e");
            if (getChineseOfWord(temp, def, sizeof(def))) {
                printf("%s", def);
                return true;
            }
        }
    } else if (n==_prefix_RE||n==_prefix_DIS||n==_prefix_ANTI||n==_prefix_UN) {
        cout << Add[n];
        if (printChineseOfWord(s)) {
            return true;
        }
        return WordCutter(s);
    } else if(n==_postfix_apostrophe_S||n==_postfix_LY||n==_postfix_AL||n==_postfix_ER||n==_postfix_OR||n==_postfix_ISM||n==_postfix_IST) {
        if (printChineseOfWord(s)) {
            cout << Add[n];
            return true;
        }
        return WordCutter(s);
    } else if (n > 0) {
        if (printChineseOfWord(s)) {
            return true;
        }
    }
    return false;
}
