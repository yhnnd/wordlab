char popup(std::string& msg,int life) {
	static int y=1,prevtime=-1000;
	static bool Record=1,RecordPrev=1;
	if(msg=="#time=reset();") {
		prevtime=-1000;
		return 0;
	} else if(msg=="#time=clock();") {
		prevtime=clock();
		return 0;
	} else if(msg=="#record=true;") {
		RecordPrev = Record;
		Record = 1;
		return 0;
	} else if(msg=="#record=false;") {
		RecordPrev = Record;
		Record = 0;
		return 0;
	} else if(msg=="#record=reset();") {
		Record = RecordPrev;
		return 0;
	}
	y=((life==0)&&clock()-prevtime<=1000)?y+1:1;
	prevtime = clock();
	return popupcore(msg,life,0,y,ScreenX-10,Record);
}
char popup(std::string s) {
	return popup(s,1000);
}
