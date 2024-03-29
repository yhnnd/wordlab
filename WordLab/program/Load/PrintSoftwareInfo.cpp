void load::PrintSoftwareInfo(){
	// Trade Mark
	std::ifstream fin(TradeMarkRoute);
	if ( fin ) {
		std::string s = "";
		gotoxy(0,0);
        setColor(lightyellow, "PrintSoftwareInfo");
		while(std::getline(fin,s)) {
            std::cout<<s<<std::endl;
        }
		fin.close();
	}
	// Version
	PrintSoftwareVersion(40,0);
	// Monitor
	monitorShow(24, 0);
	// DB security
	if (db_is_secure(false,false)) {
        bsvLine("<-grn> (SECURE)");
    } else {
        bsvLine("<-red> (INSECURE)");
    }
	// User Account
	User.show(0,5,1);
}
