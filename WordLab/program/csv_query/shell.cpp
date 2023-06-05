//select * from where begin=a where end=tion
int csvqueryshell() {
	char query[256] = "";
	char queryprev[256] = "";
	int beginpoint = 0;
	string versionInfo = csvQueryShellVersion();
	for(;;){
		MessageWindow.Frame(0,0,0,ScreenX-6,10,10);
		MessageWindow.Title(1,0,ScreenX-6,versionInfo);
#ifdef __APPLE__
        gotoxy(2, 1);
#else
		gotoxy(1, 1);
#endif
        setColor(backdarkwhite, "csvqueryshell");
		cout<<">>> ";
#ifdef __APPLE__
        gotoxy(6, 1);
#else
        gotoxy(5, 1);
#endif
		beginpoint = 0;
		begin:
		if(csvQueryInput(query, beginpoint, 256, {{"wte-", "-gry"}, {"blk-", "-ylw"}}) == 0) {
            goto end;
        }
		if(query[0]=='\0') {
            goto end;
        }
		if (strindex(query,"repeat") == 0 && strlen(queryprev)) {
            memset(query, 0, sizeof(query));
			strcpy(query, queryprev);
			beginpoint = strlen(query);
            fflush(stdin);
			goto begin;
		}
		strcpy(queryprev, query);
		cout << endl;
		csvquery csvsql(query);
		csvsql.exec();
	}
end:
    setColor(lightwhite, "csvqueryshell");
    clearScreen(0, 0, ScreenX, 12);
	return 0;
}
