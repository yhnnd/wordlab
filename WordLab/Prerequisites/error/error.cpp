int errorlog(std::string s1,std::string s2,std::string s3) {
	static int prevtime = -1000, n = 0;
	int time=0;
	if (!error_monitor_lock) {
        return -1;
    } else if (s1=="#time=reset();") {
        prevtime=-1000;
        return 0;
    } else {
		recordxy(pos);
		colorrecord(color);
		if ((time=clock()) - prevtime > 1000) {
			colorsetcmd("wte-");
			clearscreen(0,0,ScreenX,n+1);
			n = 0;
		} else {
            n++;
        }
		prevtime=time;
		gotoxy(0,n);
		colorsetcmd("ylw-");
		std::cout<<s1;
		colorsetcmd("red-");
		std::cout<<" "<<s2;
		if (!s3.empty()) {
			colorsetcmd("wte-");
			std::cout<<" ("<<s3<<")";
		}
		resetxy(pos);
		colorreset(color);
		return 0;
	}
}
