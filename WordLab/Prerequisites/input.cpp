int prerequisites::listen(char *msg, const int INDEX, const bool DISPLAY, const std::initializer_list<char> TERM, const int MAX) {
	char c;
	for(int r = INDEX; r >= 0 && r < MAX; msg[++r] = 0 ) {
		begin:
		c = getch();
//        printf("char = %d ", c);
		auto n = std::find_if(TERM.begin(),TERM.end(),[c](char e) {
			return c == e;
		});
		if( c == 27 ) {// ESC
			return -2;
		} else if(n != TERM.end()) {// Terminate
			msg[r] = 0;
			return n - TERM.begin();
		} else if( c == 8 || c == 127 ) {// Backspace or Delete
			if (r>0) {
				printf("\b \b");
				msg[--r]=0;
				goto begin;
			} else {
				printf(" \b");
				msg[0]=0;
				goto end;
			}
		} else if(c==-32) {// bioskey
			return getch();
		} else if(isprint(c)) { //print
			putc(DISPLAY?c:'*',stdout);
		} else if(c=='\t') {// TABLE
			r += 3;
			strcat(msg,"    ");
			fputs("    ",stdout);
			continue;
		}
		msg[r] = c;
	}
	end:
	return -1;
}
