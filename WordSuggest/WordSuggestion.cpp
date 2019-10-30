#include <cstring>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;
char EnglishRoute[] = "all_words.txt";

bool strHasSubseq(std::string line,std::string pattern) {
	auto itr_line = line.begin(), itr_pattern = pattern.begin();
	while( itr_line != line.end() && itr_pattern != pattern.end() ) {
		if( *itr_line == *itr_pattern ) ++itr_pattern;
		++itr_line;
	}
	return itr_pattern == pattern.end();
}

void loop() {
	string keyword, wordbase;
	cout<<">>>";
	cin>>keyword;

	float substrRatio = 0.5, subseqRatio = 0.66, la, lb = keyword.length();
	set<string> matched;
	ifstream fin(EnglishRoute);
	while(!fin.eof()) {
		if(!(fin>>wordbase)) break;
		la = wordbase.length();
		if(wordbase.find(keyword) == 0 && lb/la >= substrRatio) {
			cout<<"+ "<<wordbase<<endl;
			matched.insert(wordbase);
		}
	}
	fin.clear();
	fin.seekg(ios::beg);
	while(!fin.eof()) {
		if(!(fin>>wordbase)) break;
		la = wordbase.length();
		if(strHasSubseq(wordbase,keyword) && lb/la >= subseqRatio) {
			if(matched.find(wordbase) != matched.end()) continue;
			cout<<"- "<<wordbase<<endl;
			matched.insert(wordbase);
		}
	}
	fin.close();
}

int main() {
	while (true) {
		loop();
	}
}
