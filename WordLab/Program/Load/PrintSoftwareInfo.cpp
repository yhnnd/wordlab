void PrintSoftwareInfo(){
	// Trade Mark
	std::ifstream fin(TradeMarkRoute);
	if ( fin ) {
		std::string s = "";
		gotoxy(0,0);
		colorset(lightyellow);
		while(std::getline(fin,s)) std::cout<<s<<std::endl;
		fin.close();
	}
	// Version
	PrintSoftwareVersion(22,0);
	// Monitor
	monitorShow(24,0);
	// DB security
	if(db_is_secure(false,false)) bsvline("<back green> (SECURE)");
	else bsvline("<back red> (INSECURE)");
	// User Account
	User.show(0,5,1);
}
