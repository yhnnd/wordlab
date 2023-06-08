int findReverse(const char * msg, FILE * fp, const bool close) {
	int line = 1, n = 0, r = 0;
	char c, lineInFile[256];
	if (fp == NULL) {
        errorLog("find Reverse", "error open file");
		return 0;
    }
	for (line = 1, n = 0, r = 0; (c = fgetc(fp)) != EOF; ) {
		if (c == '\n') {
		    if (strindex(lineInFile, msg) != -1) {
                n++;
            }
		    line++;
            r = 0;
            memset(lineInFile, 0, sizeof(lineInFile));
        } else {
            lineInFile[r++] = c;
        }
    }
	if (close) {
        fclose(fp);
    }
	return n;
}

int findReverse(const char *msg, const char *route){
	int n = 0;
	FILE * fpr = fopen(route,"r");
	if (fpr == NULL) {
        errorLog("find Reverse", "error open ", route);
    } else {
        n = findReverse(msg, fpr, 1);
    }
	return n;
}
