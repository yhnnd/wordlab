int postfixcore(int lth, string &word, std::vector<std::vector<std::string>> affix) {
	for(int j = affix.size(); j > 0; j--) {
        const vector<string> & affixList = affix[j - 1];
		if (lth >= j) {
			for(int i = 0; i < affixList.size() && affixList[i].length() > 0 && affixList[i][0] != '#'; i++) {
//                printf("lth=%d, j=%d, word = '%s', word.substr(lth - j) = '%s', affixList[i] = '%s'\n", lth, j, word.c_str(), word.substr(lth - j).c_str(), affixList[i].c_str());
				if (lth - j >= 0 &&
				        word.substr(lth - j) == affixList[i]//exprimt'l
				  ) {
                    lth -= j;
					if (lth > 0) {
						word.erase(lth);// exprimt'l
						postfixcore(lth, word, affix);
						colorset(lightyellow);
						cout<<" + ";
					}
					colorset(lightcyan);
					printf("%s", affixList[i].c_str());
					colorreset(lightwhite);
					return lth;
				}
			}
		}
	}
	return infix(lth, word);
}
