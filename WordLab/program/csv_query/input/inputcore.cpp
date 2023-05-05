int inputcore(char *msg,int BEGIN,bool DISPLAY,char term0,char term1,char term2,char *suggests,bool AllowNull,int SuggestWindowX) {
	int r;
	char c;

    auto listenDelete = [](int &r, char * msg) {
        if (r > 0) {
            std::cout<<" \b";
        } else {
            std::cout<<" ";
        } if (r) {
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
        c = getche();
		if (!DISPLAY && isprint(c)) {
            cout << "\b*";
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
            if(AllowNull||r>0) return 2;
            else goto begin;
        } else {
            msg[r] = c;
        }
		msg[r+1]='\0';
		if (suggests != NULL) {
            inputsuggests(suggests,msg,30,SuggestWindowX);
        }
    }
	return 0;
}

