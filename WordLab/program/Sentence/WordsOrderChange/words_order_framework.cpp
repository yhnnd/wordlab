void sts::WordsOrderFramework() {
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

	if (this->configs.rearrange_words_order.manually_set_checkers == true) {
		WordsOrderSettings(ListPos, CheckerInfo);
	}

	for(int n = 0; n < CheckerMax; n++ ) {
		if(this->configs.show_debug_message) {
			printf("\n[%d] ListPos [%d] CheckerInfo \"%s\"\n", n, ListPos[n], CheckerInfo[ListPos[n]+1].c_str());
		} else {
            status(toString(ListPos[n]), " ", CheckerInfo[ListPos[n]+1]);
        }

		WordsOrderFrameworkCore(n,ListPos);

		if(this->configs.show_debug_message) {
            // print sentence rearranged
            printf("\n=>");
            this->printSentence(this->s, this->rwin + 1, {"ylw-", "-blk"}, show_word_number);
            printf("\n");
		}
	}
}
//STS WORDS ORDER
//Since   2014/05/12
//Updated 2014/06/18 17:53
//Updated 2015/06/12 12:58
//新模式可以排列Checker執行順序.2015年6月13日
//warning:the last word is s[rwin-1], not s[rwin]!//2015/06/28
