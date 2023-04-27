void indexCore(const std::string msg,int x=10,int y=9,WORD color=darkwhite){
	recordxy(pos);
	char wordbase[LINEMAX];
	colorset(color);
	clearscreen(x,y,60,10);
	gotoxy(x,y);
	cout<<msg;
	if(!indexerror()&&IL) Select(msg.c_str(),wordbase,x,y);
	resetxy(pos);
}
