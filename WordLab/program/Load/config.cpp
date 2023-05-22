void load::animation(const int r, const int max) {
	const int margin = 10, leap = (ScreenX - 2 * margin) / max;
	progressbar Bar(1, 0);
	for (int i = 0; i <= leap; i++) {
        Bar.show(margin, ScreenY - 2, 0, r * leap + i, max * leap);
    }
}

void load::config() {
	const int max = 6;
    int r = 0, flag = 1;
	for (r = 0, flag = 1; r < max; ++r) {
		switch(r){
			case 0:  setscreen(ScreenX,ScreenY); break;
			case 1:  flag *= writeTime(LastLaunchRoute); break;
            case 2:  MessageWindow.init(); break;
			case 3:  flag *= systemDefaults(SystemDefaultsRoute, load::mode::loadDefaults); break;
			case 4:  User.initialize(AccountRoute); break;
			case 5:  if (ML) { MonitorActivate(); } break;
			default: errorlog("config","error",toString(r)); break;
		}
		if (flag == 0) {
			char ch = fatalerror(100);
            if (ch == 13 || ch == 10) {
                popup("wordlab terminated.", -1);
                exit(-1);
            } else {
                popup("override.", -1);
            }
		}
        animation(r, max);
	}
}
