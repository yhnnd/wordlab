void msgbox(PKC msg,int x,int y,int margin,PKC colorfont,PKC colorback){
	int r0, r, width = strlen(msg) + margin * 4;
    setColorByCommand(colorback, "msgbox");
	for (r0 = y; r0 <= y + margin * 2; r0++) {
		gotoxy(x,r0);
		for (r = 1; r <= width; r++) {
            std::cout<<" ";
        }
	}
    setColorByCommand(colorfont, "msgbox");
	gotoxy(x + margin * 2, y + margin);
	std::cout<<msg;
    setColor(lightwhite, "msgbox");
}
