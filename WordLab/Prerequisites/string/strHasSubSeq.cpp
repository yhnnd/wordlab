//	function strHasSubseq(line: string, pattern: string)
//	returns if pattern is a subsequence of line
bool strHasSubseq(std::string line,std::string pattern){
	auto itr_line = line.begin(), itr_pattern = pattern.begin();
	while( itr_line != line.end() && itr_pattern != pattern.end() ){
		if( *itr_line == *itr_pattern ) ++itr_pattern;
		++itr_line;
	}
	return itr_pattern == pattern.end();
}
