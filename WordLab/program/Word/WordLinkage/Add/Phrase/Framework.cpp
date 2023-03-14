void AddPhrase(const string s) {
	if(s.empty()) return;
	Dialog.output("start");
	Dialog.output("add "+s+"?");
	if(wl_getch()!=13) {
		popup("cancelled",0);
		goto end;
	}
	AddPhraseCore(s);
end:
	wait(-1,100,0);
}
