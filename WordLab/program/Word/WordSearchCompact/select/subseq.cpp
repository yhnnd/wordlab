bool SelectSubseq(string line,string pattern,float ratio){
	int la = line.length();
	float lb = pattern.length();
	if (strHasSubseq(line,pattern)&&lb/la>=ratio) {
        return true;
    }
	return false;
}
