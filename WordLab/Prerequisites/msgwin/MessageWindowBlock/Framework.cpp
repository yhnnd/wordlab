int messageblock::Switcher(char what[][LINEMAX],bool LoadDefaultSettings) {
	char key;
	recordColor(colorprev, "Switcher");
	//set window default
	max = MaxLength(&what[0][0],LINEMAX);
	if (npl <= 0) {
        npl = setnpl();
    }
	if (filelines(MsgWinNewDefaultsRoute,1) <= 0) {
        errorLog("message block", "default file lost");
		return 0;
	}
	if (LoadDefaultSettings) {
        defaultsload();
    }
	//set block default
	bw=(max<=npl)?width/max:width/npl;
	bh=height/(max/npl+1);
	xcleft=cleftindex;
	ycleft=cleftindex;
	for(n=1,nbefore=1;;) {
	    FillAll(what,nbefore,n,max);
	    nbefore = n;
	    key = getch();
		if(key == BIOSKEY){
	    	key = getch();
	    	if(key==UP) {
                key = 'w';
            }
	    	if(key==DOWN) {
                key = 's';
            }
	    	if(key==LEFT) {
                key = 'a';
            }
			if(key==RIGHT) {
                key = 'd';
            }
	    }// CANNOT FOLLOW AN 'ELSE'
	    if (key == 13) {
            return n;
        } else if (key == '0' || key == 'q' || key == 'Q') {
            n = max-1;
        } else if (key >= '1' && key <= '9') {
            n = key - '0';
        } else if (key == 'a' || key == 'A') {
            n--;
        } else if (key == 'd' || key == 'D') {
            n++;
        } else if (key == 'w' || key == 'W') {
            n -= npl;
        } else if (key == 's' || key == 'S') {
            n += npl;
        } else if (key == 8 || key == 127 || key == 27 || key == 'r' || key == 'R') {
            resetColor(colorprev, "Switcher");
			return -1;
		} else if (key == 'i' || key == 'I') {
		    Adjust();
			defaultssave();
		} else if (key == 'e' || key == 'E') {
		    n = Search(what, n);
			if (n>0) {
                resetColor(colorprev, "Switcher");
				return n;
			}
		} else if (key == 'n' || key == 'N') {
#ifdef  _data_dir
			bsvviewer(_data_dir"buf.bsv",true);
#else
			ERROR: DATA_DIRECTORY WAS NOT DECLARED.
#endif
		}
	    roll(n,n,1,max-1);
	}
    resetColor(colorprev, "Switcher");
	return -1;
}
