bool match(std::string line,std::string pattern){
	int r=0,j=line.length(),l=pattern.length();
	if(j<l) return 0;
	for(;r<l;r++){
		if(pattern[r]!=line[r]&&pattern[r]!='*') break;
	}
	return r==l;
}
