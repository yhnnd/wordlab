int messageblock::SearchCore(const char what[][LINEMAX],int max,char *keyword){
	int r;
	for(r=0;r<max;r++) if(strstr(what[r],keyword)!=NULL) break;
	if(r==max) return -1;
	return r;
}
