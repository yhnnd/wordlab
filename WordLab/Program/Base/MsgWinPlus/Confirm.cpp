bool confirm(int x=20,int y=6,int width=36){
	char msgs[MAXLINES][LINEMAX];
	if(LANGUAGE==0) loadmsg((char*)msgs,MsgWinConfirmMsgRoute0,MAXLINES,LINEMAX,1,1);
	if(LANGUAGE==1) loadmsg((char*)msgs,MsgWinConfirmMsgRoute1,MAXLINES,LINEMAX,1,1);
	if(MessageWindow.Confirm(2,x,y,width,&msgs[0][0],MAXLINES,LINEMAX)==1) return true;
	return false;
}
