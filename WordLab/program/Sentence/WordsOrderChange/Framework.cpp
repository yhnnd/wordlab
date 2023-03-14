void WordsOrderFramework() {
	vector<int> ListPos;
	vector<string> CheckerInfo;
	for(int i = 0; i < CheckerMax; i++ ) {
		ListPos.push_back( i );
	}
	ifstream fin(WordsOrderCheckersRoute1);
	string line;
	while( getline(fin,line) ) {
		CheckerInfo.push_back( line );
	}
	fin.close();
	WordsOrderFindMain();
	if( show_debug_message==true && auto_word_translation==false ) {
		WordsOrderSettings(ListPos,CheckerInfo);
	}
	for(int n = 0; n < CheckerMax; n++ ) {
		status(tostring(ListPos[n])," ",CheckerInfo[ListPos[n]+1]);
		if(show_debug_message) {
			cout<<endl<<CheckerInfo[ListPos[n]+1]<<" => ";
		}
		WordsOrderFrameworkCore(n,ListPos);
		if(show_debug_message) {// print sentence rearranged
			for(int r = 0; r < rwin; r++ ) cout<<s[r].txt<<" ";
			if(ispunct(punct)) cout<<"\b"<<punct;
		}
	}
}
//STS WORDS ORDER
//Since   2014/05/12
//Updated 2014/06/18 17:53
//Updated 2015/06/12 12:58
//新模式可以排列Checker執行順序.2015年6月13日
//warning:the last word is s[rwin-1], not s[rwin]!//2015/06/28
