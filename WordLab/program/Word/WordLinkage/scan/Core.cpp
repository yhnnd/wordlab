void WLscancore(int lth,int NOL,FILE *fp1){
	int bits = toString(NOL).length(), vol = 25;
	char word[NOL][lth+1];
	for(int i = 0; i < NOL; i++){
		fgets(word[i],lth+2,fp1);
		strclr(word[i],lth);
	}
	strsort(&word[0][0],NOL,lth+1);
	int page = 1, pagemin = 1, pagemax = ceil(NOL/vol)+1;
	for(page = pagemin;;){
		clearScreen();
		cout<<"db-"<<lth<<"-"<<NOL<<":"<<pagemax<<"-"<<page<<endl;
		for( int i = (page - 1) * vol; i < NOL and i < page * vol; ++i ){
			int lineNumber = Search(word[i],lth);
	    	cout<<setw(bits)<<i+1<<" "<<word[i]<<" "<<WLchinese(lth,lineNumber,2);
			cout<<" "<<setw(bits)<<lineNumber<<" "<<Chinese(lth,lineNumber)<<endl;
		}
		if (pagemax > pagemin) {
            page = MessageWindow.ListSwitch(page,pagemax,0,vol+1,40);
        } else {
            break;
        }
		if(page < 0) {
            break;
        }
		roll(page,page,1,pagemax);
	}
}
