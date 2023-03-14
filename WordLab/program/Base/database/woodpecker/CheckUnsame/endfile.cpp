bool endfile(const char c1[],const char c2[],const char c){
	int r;
	for(r=0;r<strlen(c1);r++) if(c1[r]==EOF) return true;
	for(r=0;r<strlen(c2);r++) if(c2[r]==EOF) return true;
	if(c==EOF) return true;
return false;
}
