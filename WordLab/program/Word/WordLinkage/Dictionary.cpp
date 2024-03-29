char WLDictionary(const std::string keyword) {
	char ReturnLetter = 0;
	string DictionaryPageFileName(string(_data_dir)+"lang/structureddictionary/"+keyword+".sdv");
	ifstream fin(DictionaryPageFileName);
	if (fin) {// file exists
		fin.close();
		bsvLine(("<blk-wte>(Press <wte-#gry>( ENTER ) to check out more about <blk-grn>( "+keyword+" ))").c_str());
		ReturnLetter = getch();
		if (ReturnLetter == 13 || ReturnLetter == 10) {
			window document;
			document.setfilename(DictionaryPageFileName);
			document.setwindow(ScreenX-2,ScreenY);
			document.setmargin(0,0,8,0);
			document.setpadding(2,2,1,1);
			document.setcolorinactive("#blu-gry","-gry","#blu-gry","-gry","gry-#blu","-#blu","#ylw-#red","-#red");
			document.setcoloractive("-wte","-wte","-gry","-gry","wte-grn","-grn","ylw-red","-red");
			document.alloc();
			document.load("", ";");
            std::__fs::filesystem::create_directory("SDV_BSV_TEMP");
			string label = SDV_to_BSV(keyword,document,"SDV_BSV_TEMP/");
			bsvLabelEnter("SDV_BSV_TEMP/",("\""+label+"\"").c_str(),0,document.margin.top,document.width,"wte-blu");
            clearScreen(0, document.margin.top - 1, document.width + 1, document.innerHeight() + 2);
			// Y = MarginTop - 1 is for bsvlines() to output filename
            std::__fs::filesystem::remove_all("SDV_BSV_TEMP");
            rmdir("SDV_BSV_TEMP");
		}
	}
	return ReturnLetter;
}
