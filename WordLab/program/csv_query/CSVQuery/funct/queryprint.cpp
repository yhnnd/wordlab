int queryPrint(){
	if(!print_msg.empty()){
		gotoxy(1, getxy().Y);
		setColor(backdarkwhite, "queryPrint");
		bsvLine(print_msg.c_str());
		print_msg.clear();
		getch();
		return 1;
	}
    return 0;
}
