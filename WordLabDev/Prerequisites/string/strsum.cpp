int strsum(const char *s){
	int r,sum=0;
	for(r=0;s[r]!=0;r++) sum+=s[r];
	return abs(sum);
}
