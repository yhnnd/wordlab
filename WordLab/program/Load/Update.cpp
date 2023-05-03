void load::UpdateDatabase(string route){

}

void load::UpdateSoftware(string route){

}

void load::Update() {
    int y = 3;
	MessageWindow.Frame(0,0,2,70,16,16);
	gotoxy(1, y);
	bsvline("<-wte>(enter file route",73);
	gotoxy(18, y);
	string msg;
	cin>>msg;
	gotoxy(1, ++y);
	bsvline("<-wte>(update database?",73);
    char c = getch();
	if (c == 13 || c == 10) {
		gotoxy(1, ++y);
		bsvline("<-wte>(<-ylw>(updating) library",73);
		UpdateDatabase(msg);
		gotoxy(1, ++y);
		bsvline("<-wte>(<-ylw>(complete)",73);
	}
	gotoxy(1, ++y);
	bsvline("<-wte>(update system?",73);
    c = getch();
	if (c == 13 || c == 10) {
		gotoxy(1,1);
		bsvline("<-wte>(<-ylw>(updating) system",73);
		UpdateSoftware(msg);
		gotoxy(1, ++y);
		bsvline("<-wte>(<-ylw>(complete)",73);
	}
	gotoxy(1, ++y);
	bsvline("<-wte>(all done",73);
	wait(-1,100,0);
	colorreset(lightwhite);
	clearscreen(0,0,76,3);//erase the popup
	clearscreen(0,2,76,18);//erase the panel
}

