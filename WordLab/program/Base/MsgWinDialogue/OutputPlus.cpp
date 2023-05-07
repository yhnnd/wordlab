void dialog::output(const string msg,WORD color,int x,int y,bool EnableBSV) {
	static bool times = false;
    static string title = "";
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
        title = msg.substr(6);
		goto end;
	}
	if (times == false) {
        MessageWindow.Frame(0,x,y,60,&blank[0][0],0,LINEMAX);
    }
    // printf("\ndialog::output msg = %s, times = %d\n", msg.c_str(), times);
    if (title.empty() == false) {
        MessageWindow.Title(x, y, 60, title);
    }
	output(msg,times,color,"",x,y,EnableBSV);
	times = true;
	end:
	colorreset(colorprev);
}
