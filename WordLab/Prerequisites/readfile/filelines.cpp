int fileLines (FILE * fp, const bool close, const bool debug) {
	int NOL = 1;
	char ch;
	if (fp == NULL) {
		if (debug) {
            errorLog("FileLines", "error opening file");
        }
		return EOF;
    } else {
        while (EOF != (ch = getc(fp))) {
            if (ch == '\n') {
                ++NOL;
            }
        }
    }
	if (close) {
        fclose(fp);
    } else {
        rewind(fp);
    }
	return NOL;
}

int fileLines(const std::string route, const bool debug) {
	FILE * fp = fopen(route.c_str(), "r");
	if (fp == NULL) {
		if (debug) {
            errorLog("FileLines", "cannot open ", route);
        }
		return EOF;
    } else {
        return fileLines(fp, 1, debug);
    }
}
