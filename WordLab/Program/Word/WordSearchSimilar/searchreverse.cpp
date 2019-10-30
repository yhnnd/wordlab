void SearchReverse(){
	string s;
	const char tempfilename[]="buf.dat";
	for(;;){
	    Dialog.output("start");
		Dialog.output("search:",lightgreen);
		cin>>s;
		remove(tempfilename);
		for(int r=1;r<=30;r++) findinfile(s,LibraryRoute(r,lang::CH),tempfilename);
		file_filter_comma(tempfilename);//Essential
		MessageWindow.bsvviewer("buf.dat",0,10,0,ScreenX-20,ScreenY-2,false);
	    if(popup("press [ENTER] to continue",-1)!=13) break;
	}
	Dialog.output("reset");
}
