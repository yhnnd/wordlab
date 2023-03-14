bool SelectSubstr(string line,string pattern,float ratio){
	float la = line.length();
	float lb = pattern.length();
	if(line.find(pattern)==0&&lb/la>=ratio) return true;
	return false;
}
