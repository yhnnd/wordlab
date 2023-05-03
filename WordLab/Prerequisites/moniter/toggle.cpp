void monitorSet(bool *lock){
	int x=0,y=1,width=ScreenX-10-x;
	(deny(*lock,*lock))?MonitorActivate():MonitorDisable();
	progressbar Bar(1,0);
	for(int i=0;i<=width;i++,Sleep(1000/width)) {
		Bar.show(x+4,0,0,i,width);
	}
	popup("<-wte>(monitor  ",
		(*lock)?"<grn-wte>(ON )":"<red-wte>(OFF)",
		"  ",
		"<grn-wte> (enabled) ",toString(MonitorGetNumber()),
		"<red-wte> (disabled) ",toString(2-MonitorGetNumber()),
		0);
}
