std::string Translation(const std::string word,int defNumber = 1);
std::string Translation(const std::string word,int defNumber) {
	const int lth = word.length();
	const int pos = Search(word.c_str(), lth, false);
	return pos ? Chinese(lth,pos,defNumber) : word;
}
// updated on 1st May 2017
