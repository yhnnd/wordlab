bool PhraseCheckerCoreKernel(int len,char S[][30]) {
	int i;
	for(i=1; i<=len; i++) if(strcmp(s[rwout+i-1].txt,S[i-1])) return false;
	if(i==len+1) {
		if(PhraseCheckerAsk(len,S)) {
			colorset(light|purple);
			cout<<S[len];
		}
		return true;
	}
	return false;
}
