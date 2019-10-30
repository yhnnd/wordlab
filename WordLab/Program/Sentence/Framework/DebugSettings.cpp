bool DebugSettings() {
	bool Continue = true;
	int x = 20, y = 0, width = 40, r = 0, rprev = 0, total = 3;
	char msgs[][LINEMAX] = {
		"<-gry>(configuration",
		"<-gry>(show debug information",
		"<-gry>(translate automatically",
		"<-gry>(rearrange words order",
		"<-gry>(done"
	};
	int max = sizeof(msgs) / sizeof(msgs[0]);
	bool background = MessageWindow.SetBackground(true);
	bool monochrome = MessageWindow.SetMonochrome(true);
	MessageWindow.Show(x,y,width,&msgs[0][0],max,LINEMAX);
	for(;; rprev=r) {
		togglesShow(x,y,width,false,total,show_debug_message,auto_word_translation,rearrange_words_order);
		r = MessageWindow.Switch(x,y,width,&msgs[0][0],max,LINEMAX,rprev);
		toggles(x,y,width,false,r,total,&show_debug_message,&auto_word_translation,&rearrange_words_order);
		if( r <= 0 ) {// quit
			Continue = false;
			break;
		} else if( r >= max-1 ) {
			Continue = true;
			break;
		}
	}
	MessageWindow.Hide(x,y,width,max,LINEMAX);
	MessageWindow.SetBackground(background);
	MessageWindow.SetMonochrome(monochrome);
	return Continue;
}
