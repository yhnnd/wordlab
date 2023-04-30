int queryprint(){
	if(!print_msg.empty()){
		gotoxy(1, getxy().Y);
		colorset(backdarkwhite);
		bsvline(print_msg.c_str());
		print_msg.clear();
		getch();
		return 1;
	}
    return 0;
}
