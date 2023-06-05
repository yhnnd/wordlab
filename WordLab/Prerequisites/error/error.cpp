int errorLog(std::string s1, std::string s2, std::string s3) {
	static int prevtime = -1000, n = 0;
	int time=0;
	if (error_monitor_lock == false) {
        return -1;
    } else if (s1 == "#time=reset();") {
        prevtime = -1000;
        return 0;
    } else {
		recordxy(pos);
		recordColor(color, "errorLog");
		if ((time=clock()) - prevtime > 1000) {
            setColorByCommand("wte-", "errorLog");
			clearScreen(0,0,ScreenX,n+1);
			n = 0;
		} else {
            n++;
        }
		prevtime=time;
		gotoxy(0,n);
        setColorByCommand("ylw-", "errorLog");
		std::cout<<s1;
        setColorByCommand("red-", "errorLog");
		std::cout<<" "<<s2;
		if (!s3.empty()) {
            setColorByCommand("wte-", "errorLog");
			std::cout<<" ("<<s3<<")";
		}
		resetxy(pos);
        resetColor(color, "errorLog");
		return 0;
	}
}
