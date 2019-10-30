std::string Translation(const std::string word,int defNumber = 1);
std::string Translation(const std::string word,int defNumber){
	int lth = word.length();
	int pos = Search(word.c_str(),lth);
	return pos ? Chinese(lth,pos,defNumber) : word;
}
// updated on 1st May 2017
