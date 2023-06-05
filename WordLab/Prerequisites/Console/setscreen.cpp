void setScreen(int w, int h) {
#if defined(_WIN32)
    char s[8],msg[64]="mode CON: ";
	if(w>0){
		strcat(msg," COLS=");
		strcat(msg,itoa(w,s,10));
	}
	if(h>0){
		strcat(msg," LINES=");
		strcat(msg,itoa(h,s,10));
	}
	system(msg);
#endif
}
