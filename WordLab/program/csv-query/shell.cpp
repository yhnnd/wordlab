int csvqueryshell(){
	char query[256];
	char queryprev[256];
	int beginpoint=0;
	string versionInfo = csvQueryShellVersion();
	for(;;){
		MessageWindow.Frame(0,0,0,ScreenX-6,10,10);
		MessageWindow.Title(1,0,ScreenX-6,versionInfo);
		gotoxy(1,1);
		colorset(backdarkwhite);
		cout<<">>> ";
		beginpoint=0;
		begin:
		if(csvQueryInput(query, beginpoint, 256, backdarkwhite, backlight | backyellow) == 0) goto end;
		if(query[0]=='\0') goto end;
		if(strindex(query,"repeat")==0){
			strcpy(query,queryprev);
			beginpoint=strlen(query);
			goto begin;
		}
		strcpy(queryprev,query);
		cout<<endl;
		csvquery csvsql(query);
		csvsql.exec();
	}
end:
	colorreset(lightwhite);
	clearscreen(0,0,ScreenX,12);
	return 0;
}
