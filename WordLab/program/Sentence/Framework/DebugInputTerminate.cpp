int InputDebugTerm() {
	int r;
	for(r = 0, punct = 0; s[rwin].txt[r] != 0; r++) {
		if(isalpha(s[rwin].txt[r])||s[rwin].txt[r]=='\'');
		else {
			punct = s[rwin].txt[r];
			s[rwin].txt[r] = 0;
			break;
		}
	}
	return punct;
}
