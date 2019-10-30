int WordInsert(){
	char label[]="\"main\"",line[64];
	int x=10,y=3,width=55,h=10;
	MessageWindow.Frame(0,x,y,width,h,h);
	scriptprocessor script(0,32,AddWordScriptFolder);
	bsvLabelEnter(AddWordScriptFolder.c_str(),label,x+1,y+1,width+3,"wte-blu",&script);
	if(loadmsg(line,"out.dat",1,64,1,1)>0){
		popup("<-wte>(",0);
		recordxy(pos);
		gotoxy(1,1);
		colorset(bsvcmdcolor("#blu-ylw"));
		cout<<"def:";
		colorset(bsvcmdcolor("-wte"));
		cout<<"("<<line<<")";
		resetxy(pos);
		if(MessageWindow.alert("<-wte>(add this def?",2,20,5,36,4,10)==1){
			// add def to library
			popup("<-grn>(<-ylw>( new definition ) added",0);
		}else popup("<-red>( addition of <-ylw>( new definition ) cancelled",0);
	}else popup("<-gry>(<-red>( error ) new definition not found",0);
	return 0;
}
