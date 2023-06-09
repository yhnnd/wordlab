void WLScanCore(int lth, int NOL, FILE *fp1){
	const int bits = toString(NOL).length(), vol = 25;
	char word[NOL][lth+1];
	for(int i = 0; i < NOL; i++){
		fgets(word[i],lth+2,fp1);
		strclr(word[i],lth);
	}
	strsort(&word[0][0],NOL,lth+1);
	int page = 1, pagemin = 1, pagemax = ceil(NOL/vol)+1;
	for(page = pagemin;;){
		clearScreen();
		cout << "db lth = "<< lth;
        cout << ", nol = " << NOL;
        cout << ", total page = " << pagemax;
        cout << endl;
		for( int i = (page - 1) * vol; i < NOL and i < page * vol; ++i ) {
			int lineNumber = Search(word[i], lth, false);
	    	cout<<setw(bits)<< i + 1 <<" "<<word[i] << " " << WLChinese(lth,lineNumber,2);
            const auto & definitionsVector = getWordDefinitions(lth, lineNumber);
            const std::string definitionText = definitionsVector.size() ? definitionsVector[0].text : "";
			cout << " " << setw(bits) << lineNumber << " " << definitionText << endl;
		}
		if (pagemax > pagemin) {
            gotoxy(0, vol + 1);
            cout << page << "/" << pagemax;
            page = MessageWindow.ListSwitch(page, pagemax, 6, vol + 1, ScreenX - 12);
        } else {
            break;
        }
		if(page < 0) {
            break;
        }
		roll(page,page,1,pagemax);
	}
}
