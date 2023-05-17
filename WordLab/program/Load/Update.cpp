void load::UpdateDatabase(string route){

}

void load::UpdateSoftware(string route){

}

void load::Update() {
    int x = 1, y = 3;
#ifdef __APPLE__
    x = 2;
#endif
	MessageWindow.Frame(0,0,2,70,16,16);

	gotoxy(x, y);
	bsvline("<-wte>(enter file route",73);

	string msg = "";

    ::fflush(stdin);
    gotoxy(x + 17, y);
	cin >> msg;

	gotoxy(x, ++y);
	bsvline("<-wte>(update database?",73);

    ::fflush(stdin);
    char c = getch();

	if (c == 13 || c == 10) {
		gotoxy(x, ++y);
		bsvline("<-wte>(<-ylw>(updating) library",73);
		UpdateDatabase(msg);
		gotoxy(x, ++y);
		bsvline("<-wte>(<-grn>(complete)",73);
	}

	gotoxy(x, ++y);
	bsvline("<-wte>(update system?",73);

    ::fflush(stdin);
    c = getch();

	if (c == 13 || c == 10) {
		gotoxy(x, ++y);
		bsvline("<-wte>(<-ylw>(updating) system",73);
		UpdateSoftware(msg);
		gotoxy(x, ++y);
		bsvline("<-wte>(<-grn>(complete)",73);
	}
	gotoxy(x, ++y);
	bsvline("<-wte>(all done",73);
	wait(-1, 100, 0);
	colorreset(lightwhite);
	clearscreen(0,0,76,3);//erase the popup
	clearscreen(0,2,76,18);//erase the panel
}

