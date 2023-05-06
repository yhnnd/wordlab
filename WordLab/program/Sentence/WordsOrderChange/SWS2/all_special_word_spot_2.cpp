int sts::SWS2_WordPos(int r) {
    int listpos;
    switch (r) {
        case 0:
            listpos=49;
            break;//in
        case 1:
            listpos=51;
            break;//on
        case 2:
            listpos=66;
            break;//behind
        case 3:
            listpos=68;
            break;//above
        case 4:
            listpos=75;
            break;//outside
        case 5:
            listpos=76;
            break;//inside
        case 6:
            listpos=77;
            break;//upon
        case 7:
            listpos=78;
            break;//into
        case 8:
            listpos=79;
            break;//onto
        case 9:
            listpos=80;
            break;//under
        case 10:
            listpos=81;
            break;//beneath
        case 11:
            listpos=91;
            break;//within
        case 12:
            listpos=93;
            break;//amid
        default:
            listpos=0;
            break;
    }
    return listpos;
}


void sts::SWS2_FindNoun(int prepnumber) {
    auto & prep = this -> prepositions[prepnumber];
    int r;
    for(r = prep.begin.pos + 1; r <= rwin; r++) {
        if (
//                (SortEX(s[r].txt,"REALNOUN")==0&&SortEX(s[r+1].txt,"REALNOUN")!=0)
//                ||(SortEX(s[r].txt,"NOUN")==0&&SortEX(s[r+1].txt,"NOUN")!=0)
//                ||(wordSortIncludes(s[r].txt, {1}) && wordSortIncludes(s[r+1].txt, {11}))
//                || r== rwin
                (
                        wordSortIncludes(this->s[r].txt, {1, 8, 3, 11})
                        ||
                        wordSortIsNoType(this->s[r].txt) == true
                ) && ( r == rwin || (
                        wordSortIncludes(this->s[r + 1].txt, {1, 8, 3, 11}) == 0
                        &&
                        wordSortIsNoType(this->s[r + 1].txt) == false
                    )
                )
        ) {
            prep.end.pos = r;
            break;
        }
    }
}

//介词翻譯位置可能不正确
void sts::SpecialWordSpot2Preposition() {
    const int specialmax = filelines(SpecialWordsRoute,true);
    if( specialmax <= 0 ) {
        popup("cannot find <red>(",SpecialWordsRoute,")",0);
        return;
    }
    int specialpos[specialmax];
    memset(specialpos, -1, sizeof(specialpos));
    {
        char specialword[specialmax][30];

        loadmsg((char*)specialword,SpecialWordsRoute,specialmax,30,1,1);

        for(int r0 = 1; r0 <= specialmax; r0++) {
            for(int r = 0; r<=rwin; r++) {
                if(strcmp(specialword[r0],s[r].txt)==0) {
                    specialpos[r0] = r;
                    break;
                }
            }
        }
    }

    {
        ifstream fin1(PrepTrans0Route);
        if (!fin1) {
            return;
        }
        prepositions.clear();
        preposition preposition;
        preposition.begin.pos = -1;
        preposition.begin.defs = "";
        preposition.end.pos = -1;
        preposition.end.defs = "";
        string line = "";
        while (getline(fin1, line)) {
            preposition.begin.defs = line;
            prepositions.push_back(preposition);
        }
        fin1.close();
        ifstream fin2(PrepTrans1Route);
        if (!fin2) {
            return;
        }
        int i = 0;
        while (getline(fin2, line)) {
            prepositions[i].end.defs = line;
            ++i;
        }
        fin2.close();
        for(int r = 0; r < prepositions.size(); r++) {
            const int r1 = SWS2_WordPos(r);
            if (specialpos[r1] >= 0) {
                this->prepositions[r].begin.pos = specialpos[r1];
                SWS2_FindNoun(r);
                popup("SWS2: prep <ylw->(\"",s[this->prepositions[r].begin.pos].txt,"\") has been found.", 0);
            }
        }
    }
}
