void WLdblogprocessor(std::string filename){
	window document;
	document.setfilename(filename);
	document.setwindow(ScreenX,ScreenY);
	document.setmargin(2,2,3,3);
	document.setpadding(0,0,1,1);
	document.setcolorinactive("-gry","-gry","-gry","-gry","gry-#blu","-#blu","#ylw-#red","-#red");
	document.setcoloractive("-wte","-wte","-wte","-wte","wte-blu","-blu","ylw-red","-red");
	document.alloc();
	document.load("","");
	openlogwithpsf(document,filename+".js");
}
// Created on April-29-2017
