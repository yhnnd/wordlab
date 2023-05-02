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
    int r;
    for(r=preppos0[prepnumber]+1; r<=rwin; r++)
        if((SortEX(s[r].txt,"REALNOUN")==0&&SortEX(s[r+1].txt,"REALNOUN")!=0)
           ||(SortEX(s[r].txt,"NOUN")==0&&SortEX(s[r+1].txt,"NOUN")!=0)
           ||(WordSort(s[r].txt)==1&&WordSort(s[r+1].txt)==11)
           ||r==rwin) {
            preppos1[prepnumber]=r;
            break;
        }
}

//介词翻譯位置可能不正确
void sts::SpecialWordSpot2Preposition() {
    int r,r0,r1;
    int specialmax = filelines(SpecialWordsRoute,true);
    if( specialmax <= 0 ) {
        popup("cannot find <red>(",SpecialWordsRoute,")",0);
        return;
    }
    char specialword[specialmax][30];
    int  specialpos[specialmax];
    loadmsg((char*)specialword,SpecialWordsRoute,specialmax,30,1,1);
    loadmsg((char*)preptrans0,PrepTrans0Route,maxprep,preplth,1,1);
    loadmsg((char*)preptrans1,PrepTrans1Route,maxprep,preplth,1,1);
    memset(specialpos,-1,sizeof(specialpos));
    memset(preppos0,-1,sizeof(preppos0));
    memset(preppos1,-1,sizeof(preppos1));
    for(r0=1; r0<=specialmax; r0++) {
        for(r=0; r<=rwin; r++) {
            if(strcmp(specialword[r0],s[r].txt)==0) {
                specialpos[r0]=r;
                break;
            }
        }
    }
    for(r=0; r<maxprep; r++) {
        r1 = SWS2_WordPos(r);
        if(specialpos[r1]>=0) {
            preppos0[r] = specialpos[r1];
            SWS2_FindNoun(r);
            popup("SWS2: prep <yellow>(",s[preppos0[r]].txt,") has been found.",0);
        }
    }
}
