void load::animation(int r,int max) {
	int margin=10,leap=(ScreenX-2*margin)/max;
	progressbar Bar(1,0);
	for(int i=0;i<=leap;i++) Bar.show(margin,ScreenY-2,0,r*leap+i,max*leap);
}
void load::config() {
	int r = 0, max = 6;
	bool flag = 1;
	for(r=0;r<max;animation(r++,max)){
		switch(r){
			case 0:  setscreen(ScreenX,ScreenY);break;
			case 1:  flag*=writeTime(LastLaunchRoute);break;
			case 2:  flag*=defaults(DefaultsRoute,true);break;
			case 3:  MessageWindow.init();break;
			case 4:  User.initialize(AccountRoute);break;
			case 5:  if(ML) MonitorActivate();break;
			default: errorlog("config","error",tostring(r));break;
		}
		if(!flag){
			char ch = fatalerror(100);
            if (ch == 13) {
                popup("wordlab terminated.", -1);
                exit(-1);
            } else {
                popup("override.", -1);
            }
		}
	}
}
