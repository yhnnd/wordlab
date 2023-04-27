int queryprint(){
	if(!print_msg.empty()){
		cursormove(1,0);
		colorset(backdarkwhite);
		bsvline(print_msg.c_str());
		print_msg.clear();
		wl_getch();
		return 1;
	}
    return 0;
}
