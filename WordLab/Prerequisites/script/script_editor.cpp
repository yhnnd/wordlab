// Used by Prerequisites::scriptShell()
int ScriptEditor(std::string filename) {
    int returnValue = 0;
	window document;
	document.setfilename(filename);
	document.setwindow(ScreenX/2,ScreenY);
	document.setmargin(0,0,3,3);
	document.setpadding(2,2,1,1);
	document.setcolorinactive("#blu-gry","-gry","#blu-gry","-gry","gry-#blu","-#blu","#ylw-#red","-#red");
	document.setcoloractive("#blu-wte","-wte","#blu-wte","-wte","wte-grn","-grn","ylw-red","-red");
	document.alloc();
	document.load("",";");
	returnValue = document.Editor();
	document.save("",";");
    return returnValue;
}
