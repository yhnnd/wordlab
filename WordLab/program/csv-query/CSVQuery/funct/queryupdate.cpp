int queryupdate(string msg=""){
	if(msg.length()){
		cursormove(1,0);
		cout<<"proceeding "<<msg;
		cursormove(1,1);
	}else{
		cursormove(1,0);
		cout<<"updating "<<msg_trim;
		cursormove(1,1);
		WordUpdate(msg_trim);
	}
}
