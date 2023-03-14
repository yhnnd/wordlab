void InputDebug() {
	for( rwin = 0; rwin < MAXIMUM; ++rwin ) {
		cin >> s[rwin].txt;
		if((punct = InputDebugTerm()) == true) break;
	}
}
