int csvQueryInput(char *query,const int beginPoint,int lthmax,const vector<sts::consoleColor> colors) {
#ifdef __APPLE__
    const COORD inputPos = getxy();
#else
    const short WindowX = 2;
    const COORD inputPos = {static_cast<short>(WindowX), getxy().Y};
#endif
	char msg[32];
	char suggests[]=
	    "if,else,where,from,to,in,of,between,and,or,not,"
	    "select,create,delete,insert,update,drop,add,open,set,alter,var,"
	    "order by,group by,join,check,print,system info,library,source,"
	    "word:en,word:en-ch,phrase:en-ch,voca:en,lth=,sort=,word=,value=,text=,"
	    "affix=,substr=,index=,prefix=,begin=,start=,suffix=,postfix=,end=,infix=,inside=,mid=,"
	    "regex=,match=,like=,pattern=,contains=,subset=,strorder=;";
	strclr(query, beginPoint);
	recordxy(pos);
	if (beginPoint > 0) {
        setForegroundColorAndBackgroundColor("blk-", "-cyn");
        gotoxy(inputPos);
		printf("%s", query);
	}
	for (int i = 0; ; ++i) {
		setForegroundColorAndBackgroundColor(colors[0].foregroundColor, colors[0].backgroundColor);
        vector<char> terms = {13, 10};
        if (i > 0) {
            terms.push_back(' ');
        }
		if (inputCore(msg, 0, true, terms, suggests, true, {static_cast<short>(inputPos.X + strlen(query)), inputPos.Y}) == -1) {
			if (i == 0 && msg[0] == '\0' && query[0] == '\0') {
                return 0;
            } else {
                setForegroundColorAndBackgroundColor("blk-", "-red");
                cout<<"\b \b";
                setForegroundColorAndBackgroundColor("blu-", "-gry");
                if (inputCore(query, strlen(query), true, {13, 10}, suggests, true, inputPos) == -1) {
                    strcat(query," ");
                    return 0;
                }
                break;
            }
		}
		if (msg[0] == '\0') {
            break;
        }
		strcat(query,msg);
		strcat(query," ");
		gotoxy(pos);
		setForegroundColorAndBackgroundColor(colors[1].foregroundColor, colors[1].backgroundColor);
		cout << query;
	}
	resetxy(pos);
	return 1;
}
