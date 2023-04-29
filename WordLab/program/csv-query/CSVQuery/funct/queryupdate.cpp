int queryupdate(string msg=""){
	if(msg.length()){
		gotoxy(1, getxy().Y);
		cout<<"proceeding "<<msg;
		gotoxy(1, getxy().Y + 1);
	}else{
		gotoxy(1, getxy().Y);
		cout<<"updating "<<msg_trim;
		gotoxy(1, getxy().Y + 1);
		WordUpdate(msg_trim);
	}
    return 0;
}
