void UpdateDatabase(string route){
}
void UpdateSoftware(string route){
}
void Update(){
	MessageWindow.Frame(0,0,2,70,16,16);
	gotoxy(1,3);
	bsvline("<-wte>(enter file route",73);
	gotoxy(18,3);
	string msg;
	cin>>msg;
	gotoxy(1,4);
	bsvline("<-wte>(update database?",73);
	if(wait(-1,100,1)==13){
		cursormove(1,1);
		bsvline("<-wte>(<-ylw>(updating) library",73);
		UpdateDatabase(msg);
		cursormove(1,1);
		bsvline("<-wte>(<-ylw>(complete)",73);
	}
	cursormove(1,1);
	bsvline("<-wte>(update system?",73);
	if(wait(-1,100,1)==13){
		cursormove(1,1);
		bsvline("<-wte>(<-ylw>(updating) system",73);
		UpdateSoftware(msg);
		cursormove(1,1);
		bsvline("<-wte>(<-ylw>(complete)",73);
	}
	cursormove(1,1);
	bsvline("<-wte>(all done",73);
	wait(-1,100,0);
	colorreset(lightwhite);
	clearscreen(0,0,76,3);//erase the popup
	clearscreen(0,2,76,18);//erase the panel
}

