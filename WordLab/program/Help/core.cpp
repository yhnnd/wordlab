//deprecated version uses sayfile()
//updated on 2017.03.08
void HelpCore(const string Route0,const string Route1){
	window Document;
	Document.setfilename(LANGUAGE==0?Route0.c_str():Route1.c_str());
	Document.setwindow(ScreenX,ScreenY);
	Document.setmargin(36,4,5,3);
	Document.setpadding(0,0,1,1);
	Document.setcolorinactive("#blu-gry","-gry","#blu-gry","-gry","gry-#blu","-#blu","#ylw-#red","#ylw-#red");
	Document.setcoloractive("-wte","-wte","-wte","-wte","wte-blu","-blu","ylw-red","ylw-red");
	Document.alloc();
	Document.load();
	Document.Editor();
	Document.clear();
}
