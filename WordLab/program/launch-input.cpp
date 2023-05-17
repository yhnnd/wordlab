void InputForLaunch(char *msg,WORD colorStart,WORD colorEnd) {
	char suggests[]=
	    "query(),volume(),checkupdate(),update(),database(),software(),clearcache(),"
	    "addnew(),addword(),addphrase(),script(),sortlib(),"
	    "crossword(),lastlaunch(),searchcompact(),wordlinkage(),translater(),translaterpro(),"
	    "settings.engines(),settings.values(),settings.system(),settings.history(),"
	    "user.login(),list(),help(),settings.version(),"
	    "wordsortcheck(),searchreverse(),searchsimilar(),"
	    "practices(),similar();";
	auto pos = getxy();
	auto colorprev = getcolor();
	colorset(colorStart);
	inputcore(msg,0,true,13,KEY_ESC,'=',suggests,true,pos.X+1);
	gotoxy(pos);
	colorset(colorEnd);
	cout<<msg;
	colorreset(colorprev);
}
