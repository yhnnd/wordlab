int inputcore(char *msg,int BEGIN,bool DISPLAY,char term0,char term1,char term2,const char *suggests,bool AllowNull,const COORD SuggestsWindowPos) {
	int r;
	char c;

    auto listenDelete = [&SuggestsWindowPos](int &r, char * msg) {
        if (r > 0) {
//            setForegroundColorAndBackgroundColor("blk-", "-red");
            printf("\b \b");
        } else {
//            setForegroundColorAndBackgroundColor("blk-", "-blu");
            printf(" ");
        }
        if (r) {
            msg[r-1] = 0;
            r--;
        } else {
            r = 0;
            strclr(msg);
            return true;
        }
        return false;
    };

    for (r = BEGIN; ; r++) {
		begin:
        c = getch();

        if (isprint(c) == true) {
            gotoxy(SuggestsWindowPos.X + r, SuggestsWindowPos.Y);
            if (DISPLAY == false) {
//                setForegroundColorAndBackgroundColor("wte-", "-blk");
                printf("*");
            } else {
//                setForegroundColorAndBackgroundColor("blk-", "-cyn");
                printf("%c", c);
            }
        }

		if (c == 8 || c == 127 || c == 27) {
            if (listenDelete(r, msg) == true) {
                return -1;
            } else {
                goto begin;
            }
        } else if (c == term0) {
            strclr(msg,r);
            if (AllowNull||r>0) {
                return 0;
            } else {
                goto begin;
            }
        } else if(c==term1) {
            strclr(msg, r);
            if(AllowNull||r>0) {
                return 1;
            } else {
                goto begin;
            }
        } else if(c==term2) {
            strclr(msg,r);
            if (AllowNull||r>0) {
                return 2;
            } else {
                goto begin;
            }
        } else {
            msg[r] = c;
            msg[r + 1] = '\0';
        }
		if (suggests != NULL) {
            inputsuggests(suggests,msg,30,SuggestsWindowPos);
            gotoxy(SuggestsWindowPos.X + r + 1, SuggestsWindowPos.Y);
        }
    }
	return 0;
}

