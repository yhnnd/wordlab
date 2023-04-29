void dialog::output(const string msg,WORD color,int x,int y,bool EnableBSV) {
	static bool times = false;
	char blank[MAXLINES][LINEMAX] = {" "," "," "," "," "," "," "," "," "," "," "};
	colorrecord(colorprev);
	if (msg=="reset") {
		times = false;
		MessageWindow.Frame(-1,x,y,60,&blank[0][0],0,LINEMAX);
		goto end;
	}
	if (msg=="start") {
		times = false;
		MessageWindow.Frame( 0,x,y,60,&blank[0][0],0,LINEMAX);
		goto end;
	}
	if (msg.find("title:") == 0) {
		recordxy(cursor_pos);//Essential
		MessageWindow.Title(x,y,60,msg.substr(6));
	    resetxy(cursor_pos);//Essential
		goto end;
	}
	if (times == false) {
        MessageWindow.Frame(0,x,y,60,&blank[0][0],0,LINEMAX);
    }
    // printf("\ndialog::output msg = %s, times = %d\n", msg.c_str(), times);
	output(msg,times,color,"",x,y,EnableBSV);
	times = true;
	end:
	colorreset(colorprev);
}
