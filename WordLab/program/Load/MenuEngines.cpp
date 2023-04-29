void load::Engines() {
	int x = 0, y = 9, width = 30, r, rprev = 0, total = 11;
	char Menu[20][LINEMAX];
	if(LANGUAGE==0) loadmsg((char*)Menu,SetEnginesRoute"en.csv",20,LINEMAX,1,1);
	if(LANGUAGE==1) loadmsg((char*)Menu,SetEnginesRoute"ch.csv",20,LINEMAX,1,1);
	bool background = MessageWindow.SetBackground(true);
	MessageWindow.Frame(0,x,y,width,&Menu[0][0],0);
	for(;; rprev=r,defaults(DefaultsRoute,false)) {
		togglesShow(x,y,width,_Show,total+2,AL,BL,SL,DL,CL,Ctype,IL,ColorL,LANGUAGE,version,_Show,true,ML);
		r = MessageWindow.Switch(x,y,width,&Menu[0][0],0,LINEMAX,rprev);
		toggles(x,y,width,_Show,r,total,&AL,&BL,&SL,&DL,&CL,&Ctype,&IL,&ColorL,&LANGUAGE,&version,&_Show);
		if(r>=0&&r<=total);
		else if(r == total + 1) SetChineseColor(CLRL);
		else if(r == total + 2) monitorSet(&ML);
		else goto END;
	}
END:
	MessageWindow.SetBackground(background);
}
