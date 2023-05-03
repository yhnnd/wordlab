int SortClassify(char *sort) {
	int n = 0;
	if (strindex(sort,"/art./")!=-1) {
        n = 11;
    }
	if (strindex(sort,"/adj./")!=-1) {
        n = 3;
    }
	if (strindex(sort,"/n./")!=-1) {
        n = 1;
    }
	if (strindex(sort,"/pron./")!=-1) {
        n = 8;
    }
	if (strindex(sort,"/conj./")!=-1) {
        n = 10;
    }
	if (strindex(sort,"/prep./")!=-1) {
        n = 7;
    }
	if (strindex(sort,"/adv./")!=-1) {
        n = 4;
    }
	if (strindex(sort,"/aux./")!=-1) {
        n = 9;
    }
	if (strindex(sort,"/vi./")!=-1) {
        n = 6;
    }
	if (strindex(sort,"/vt./")!=-1) {
        n = 5;
    }
	if (strindex(sort,"/v./")!=-1) {
        n = 2;
    }
	return n;
}
