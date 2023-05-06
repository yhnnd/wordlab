int SpecialWordCheck(char specialword[][30],int max) {
	int  r;
	char keyword[LINEMAX];
	bool specialflag = false;
	Dialog.output("start");
	for(;; specialflag=false) {
		strcpy(keyword, Dialog.input().c_str());
		if(Dialog.getInputResult()==-1) {
            goto end;
        }
		SortDisplay(keyword);
		for(r=0; r<=max; r++) {
            if(strcmp(keyword,specialword[r])==0) {
                Dialog.output("Special: " + toString(r) + " \"" + specialword[r] + "\"", lightcyan);
                specialflag = true;
            }
        }
		if(!specialflag) {
			if (wordSort(keyword).size()) {
                Dialog.output(string("Normal: \"") + keyword + "\"", lightyellow);
            } else {
                Dialog.output(string("Unknown: \"") + keyword + "\"", lightred);
            }
		}
	}
end:
	Dialog.output("reset");
	return 0;
}
