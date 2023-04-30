int csvQueryInput(char *query,int begin,int lthmax,WORD clr1,WORD clr2) {
	int i, WindowX = 2;
	char msg[32];
	char suggests[]=
	    "if,else,where,from,to,in,of,between,and,or,not,"
	    "select,create,delete,insert,update,drop,add,open,set,alter,var,"
	    "order by,group by,join,check,print,system info,library,source,"
	    "word:en,word:en-ch,phrase:en-ch,voca:en,lth=,sort=,word=,value=,text=,"
	    "affix=,substr=,index=,prefix=,begin=,start=,suffix=,posfix=,end=,infix=,inside=,mid=,"
	    "regex=,match=,like=,pattern=,contains=,subset=,strorder=;";
	strclr(query,begin);
	recordxy(pos);
	if(begin>0) {
		colorset(backlight|backcyan);
		cout<<query;
	}
	for(i=0;; i++) {
		colorset(clr1);
		if(inputcore(msg,0,true,13,13,i>0?' ':13,suggests,i>0,WindowX)==-1) {
			if(i==0&&query[0]=='\0') return 0;
			cout<<"\b \b";
			if(inputcore(query,strlen(query)-1,true,13,13,13,suggests,i>0,WindowX)==-1) {
				strcat(query," ");
				return 0;
			}
			break;
		}
		if(msg[0]=='\0') break;
		strcat(query,msg);
		strcat(query," ");
		gotoxy(pos);
		colorset(clr2);
		cout<<query;
	}
	resetxy(pos);
	return 1;
}
