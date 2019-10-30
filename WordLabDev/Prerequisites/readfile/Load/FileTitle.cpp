const char *FileTitle(const char *msg,int slashlimit=3){
	int n=0,r=strlen(msg);
	for(;r>0&&n<slashlimit;r--) if(msg[r]=='\\') ++n;
	return &msg[++r];
}
