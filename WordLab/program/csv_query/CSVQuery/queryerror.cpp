int queryErrorPrint(string msg){
	gotoxy(1, getxy().Y);
	bsvLine(msg.c_str(),prerequisites::ScreenX-3);
	gotoxy(1, getxy().Y + 1);
	setColor(lightwhite, "queryErrorPrint");
    return 0;
}
int queryerror(const char **labels){
	char msg[128] = "<-red>(";
	strcat(msg,"<ylw-red>(");
	strcat(msg,(labels[0]==NULL)?"NULL":labels[0]);
	strcat(msg,") <-red>(");
	strcat(msg,(labels[1]==NULL)?"NULL":labels[1]);
	strcat(msg,") <wte-red>(");
	strcat(msg,(labels[2]==NULL)?"NULL":labels[2]);
	strcat(msg,") <#red-wte>(");
	strcat(msg,(labels[3]==NULL)?"NULL":labels[3]);
	strcat(msg,")");
	queryErrorPrint(msg);
    return 0;
}
int queryerror(vector<string> labels){
	string msg = "<-red>(";
	msg += "<ylw-red>(";
	msg += (labels.size()<1)?"NULL":labels[0];
	msg += ") <-red>(";
	msg += (labels.size()<2)?"NULL":labels[1];
	msg += ") <wte-red>(";
	msg += (labels.size()<3)?"NULL":labels[2];
	msg += ") <#red-wte>(";
	msg += (labels.size()<4)?"NULL":labels[3];
	msg += ")";
	queryErrorPrint(msg);
    return 0;
}
