bool PhraseCheckerAsk(int lth,char s[][30]) {
	char r,msg[LINEMAX];
	memset(msg,0,sizeof(msg));
	for(r=0; r<=lth; r++) {
		strcat(msg," ");
		strcat(msg,s[r]);
	}
	return AskChar("Phrase",tostring(lth),"<",msg,">?")==13;
}
