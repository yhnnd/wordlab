bool SearchSimilar(string word){
	int div=4;
	string tempfilename = "buf.dat", def = Translation(word);
	if(def.empty()) return 0;
	remove(tempfilename.c_str());
	for(int r=1;r<=30;r++) findinfile(def,LibraryRoute(r,lang::CH),tempfilename);
	if(def.length()>=div*2.0){
		for(int r=1;r<=30;r++){
			findinfile(def.substr(0,div),LibraryRoute(r,lang::CH),tempfilename);
		}
		for(int r=1;r<=30;r++){
			findinfile(def.substr(div),LibraryRoute(r,lang::CH),tempfilename);
		}
	}

	if(file_filter_comma(tempfilename)){
		MessageWindow.bsvviewer(tempfilename.c_str(),0,10,0,ScreenX-20,ScreenY-2,0);
		return 1;
	}
	return 0;
}
