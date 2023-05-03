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
