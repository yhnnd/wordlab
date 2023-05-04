int SortEX_BE(char *s) {
    if(strcmp(s,"am")==0
       ||strcmp(s,"is")==0
       ||strcmp(s,"was")==0
       ||strcmp(s,"are")==0
       ||strcmp(s,"were")==0
       ||strcmp(s,"be")==0
       ||strcmp(s,"been")==0
            ) {
        return 0;
    }
    return -1;
}

int SortEX_WH(char s[]) {
    if(strcmp(s,"what")==0
       ||strcmp(s,"which")==0
       ||strcmp(s,"when")==0
       ||strcmp(s,"where")==0
       ||strcmp(s,"who")==0
       ||strcmp(s,"whom")==0
       ||strcmp(s,"whose")==0
       ||strcmp(s,"how")==0
            ) {
        return 0;
    }
    return -1;
}

int SortEX_NOUN(char s[]) { // 名词家族(大)
    if(
            wordSortIncludes(s, {1, 8, 3, 4, 11})//n.//pron.//adj.//adv.//art.
            && SortEX_WH(s) != 0
            ) {
        return 0;
    }
    return -1;
}


int SortEX_REALNOUN(char s[]) { //名词家族(中)
    if (
            wordSortIncludes(s, {1, 8, 3, 11})//n.//pron.//adj.//art.
            && SortEX_WH(s) != 0
            ) {
        return 0;
    }
    return -1;
}


int SortEX_DefinitelyNOUN(char s[]) { //名词家族(小)
    if (
            wordSortIncludes(s, {1, 3, 11})//n.//adj.//art.
            ) {
        return 0;
    }
    return -1;
}



int SortEX_AD(char *s) { // adj / adv.
    if(
            wordSortIncludes(s, {3, 4})//adj. //adv.
            && SortEX_WH(s) != 0
            ) {
        return 0;
    }
    return -1;
}


int SortEX_AUX(char *s) {
    if (wordSortIncludes(s, {9})//aux.
            ) {
        return 0;
    }
    return -1;
}

bool wordSortIsAuxil(const char *word) {
    if(wordSortIncludes(word, {9})// aux.
            ) {
        return true;
    }
    return false;
}

int SortEX_VERB(char *s) {
    if(
            wordSortIncludes(s, {2, 5, 6})//verb //vt. //vi.
    ) {
        return 0;
    }
    return -1;
}


bool wordSortIsVerb (const char * word) {
    if (wordSortIncludes(word, {2, 5, 6})) {
        return true;
    }
    return false;
}


bool wordSortIsConj (const char * word) {
    if (wordSortIncludes(word, {10})) {
        return true;
    }
    return false;
}


int SortEXCore(char *s,const char *msg) {
    if(strcmp(msg,"wh")==0
       ||strcmp(msg,"wh.")==0
       ||strcmp(msg,"WH")==0
            ) {
        return SortEX_WH(s);
    } else if(strcmp(msg,"be")==0
              ||strcmp(msg,"be.")==0
              ||strcmp(msg,"BE")==0
            ) {
        return SortEX_BE(s);
    } else if(strcmp(msg,"v.")==0
              ||strcmp(msg,"verb")==0
              ||strcmp(msg,"VERB")==0
            ) {
        return SortEX_VERB(s);
    } else if(strcmp(msg,"n.")==0
              ||strcmp(msg,"noun")==0
              ||strcmp(msg,"NOUN")==0
            ) {
        return SortEX_NOUN(s);
    } else if(strcmp(msg,"realn.")==0
              ||strcmp(msg,"realnoun")==0
            ) {
        return SortEX_REALNOUN(s);
    } else if(strcmp(msg,"REALNOUN")==0
            ) {
        return SortEX_DefinitelyNOUN(s);
    } else if(strcmp(msg,"ad.")==0
              ||strcmp(msg,"adj")==0
              ||strcmp(msg,"adj.")==0
            ) {
        return SortEX_AD(s);
    } else if(strcmp(msg,"aux.")==0
              ||strcmp(msg,"aux")==0
              ||strcmp(msg,"auxil")==0
            ) {
        return SortEX_AUX(s);
    } else {
        popup("SortEX error!", -1);
    }
    return -1;
}



int SortEX(char s[],const char Message[]) {
	return SortEXCore(s,Message);
}
