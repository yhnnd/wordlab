int TranslationSelectItem(int ItemMax,string def_line,int x,int y,int width,int height) {
	int ItemNumber = 1;
	recordxy(pos);
	clearline(x,y);
	cout<<def_line;
	ItemNumber = MessageWindow.ConfirmSwitch(ItemMax,x,y+1,width,height);
	resetxy(pos);
	return ItemNumber;
}
