void WordsOrderFindMain() {
	int r,r0,r1;
FindMain:
	for(r=0,r0=-1; r<=rwin; r++) {
		if(WordSort(s[r].txt)==1) {
			r0=r;    //n.
			break;
		}
	}
	for(r=0,r1=-1; r<=rwin; r++) {
		if(WordSort(s[r].txt)==8) {
			r1=r;    //pron.
			break;
		}
	}
	for(;;) {
		if(r0>=0) {
			if(AskChar(s[r0].txt,"�����Z?")==13) {
				TheMain=r0;    //n.
				break;
			}
		}
		if(r1>=0) {
			if(AskChar(s[r1].txt,"�����Z?")==13) {
				TheMain=r1;    //pron.
				break;
			}
		}
		for(r=0; r<=rwin; r++) {
			if(AskChar(s[r].txt,"�����Z?")==13) {
				TheMain=r;    //custom
				break;
			}
		}
		break;
	}
	if(TheMain<0||TheMain>rwin) goto FindMain;
}
// S.T.S. Words Order - find Main
//Since   2014/6/18
//Updated 2014/6/18 17:53
