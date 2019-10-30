void WordsOutCore() {
	int r;
	for(r=0; r<maxprep; r++) {
		if(rwout==preppos0[r]) {
			cout<<preptrans0[r];
			return;
		}
	}
	SmartTranslater();
	for(r=0; r<maxprep; r++) {
		if(rwout==preppos1[r]) {
			cout<<preptrans1[r];
		}
	}
}
