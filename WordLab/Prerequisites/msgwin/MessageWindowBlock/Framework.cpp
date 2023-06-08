int messageBlocks::Switcher(const char what[][LINEMAX], const bool LoadDefaultSettings) {

	recordColor(colorprev, "Switcher");

	//set window default
	this->max = MaxLength(&what[0][0], LINEMAX);

	if (this->numPerLine <= 0) {
        this->numPerLine = setnpl();
    }

	if (fileLines(MsgWinNewDefaultsRoute, 1) <= 0) {
        errorLog("message block", "default file lost");
		return 0;
	}

	if (LoadDefaultSettings) {
        defaultsLoad();
    }

	// set block default
	this->blockWidth = (this->max <= this->numPerLine) ? this->width / this->max : this->width / this->numPerLine;
    this->blockHeight = this->height / (this->max / this->numPerLine + 1);
    this->xCleft = this->cleftIndex;
    this->yCleft = this->cleftIndex;

    int n, nPrev;
    char key;

	for (n = 1, nPrev = 1; ; ) {
	    FillAll(what, nPrev, n, max);
        nPrev = n;
	    key = getch();
		if (key == BIOSKEY) {
	    	key = getch();
	    	if (key == UP) {
                key = 'w';
            } else if (key == DOWN) {
                key = 's';
            } else if (key == LEFT) {
                key = 'a';
            } else if (key == RIGHT) {
                key = 'd';
            }
	    }// CANNOT FOLLOW AN 'ELSE'
	    if (key == 13 || key == 10) {
            return n;
        } else if (key == '0' || key == 'q' || key == 'Q') {
            n = max - 1;
        } else if (key >= '1' && key <= '9') {
            n = key - '0';
        } else if (key == 'a' || key == 'A') {
            n--;
        } else if (key == 'd' || key == 'D') {
            n++;
        } else if (key == 'w' || key == 'W') {
            n -= this->numPerLine;
        } else if (key == 's' || key == 'S') {
            n += this->numPerLine;
        } else if (key == 8 || key == 127 || key == 27 || key == 'r' || key == 'R') {
            resetColor(colorprev, "Switcher");
			return -1;
		} else if (key == 'i' || key == 'I') {
		    Adjust();
            defaultsSave();
		} else if (key == 'e' || key == 'E') {
		    n = Search(what, n);
			if (n > 0) {
                resetColor(colorprev, "Switcher");
				return n;
			}
		} else if (key == 'n' || key == 'N') {
#ifdef  _data_dir
			bsvviewer(_data_dir"buf.bsv", true);
#else
			ERROR: DATA_DIRECTORY WAS NOT DECLARED.
#endif
		}
	    roll(n, n, 1, this->max - 1);
	}
    resetColor(colorprev, "Switcher");
	return -1;
}
