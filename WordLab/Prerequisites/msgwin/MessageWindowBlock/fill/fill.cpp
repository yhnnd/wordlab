void messageblock::Fill(PKC msg,const COORD bpos,const int colortype,const int signal) {
	int r;
	char blank = (signal) ? ' ' : '*';//selected or not
	auto length = [&] {
		for(r=0;(r<bw*bh)&&msg[r];++r){
			if (msg[r]==',') {
				if (
                        !(r>0&&msg[r-1]=='\'' && msg[r+1]=='\'')/* not pattern "','" */
                        &&
                        !(r>0&&msg[r-1]=='\\')
                ) {
                    break;//not pattern "\,"
                }
			}
		}
		return r;
	};
	int lth = length();
	setBlockColor(colortype,signal,0);
	for (r = 0; r < bw * bh; r++) {
		gotoxy(bpos.X+r%bw, bpos.Y+r/bw);
		std::cout << blank;
	}
	setBlockColor(colortype,signal,1);
	for (r = 0; r < lth; r++) {
		gotoxy(bpos.X + r % bw + /*align center*/(bw - lth % bw) / 2,
		bpos.Y + r / bw + /*align center*/(bh - 1) / 2);
		std::cout << msg[r];
	}
	gotoxy(bpos);
}
