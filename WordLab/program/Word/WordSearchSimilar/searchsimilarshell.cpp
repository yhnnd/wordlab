void SearchSimilarShell(){
	char word[30];
	for(;;){
	    Dialog.output("start");
        Dialog.output("title: similar search");
		Dialog.output("Search:", lightgreen);
        cin.clear();
        cin.sync();
	    if (listen(word,0,1,{13,0,EOF},30) == -1) {
            break;
        }
		if(!SearchSimilar(word)) {
            popup("can not find \"", word, "\"", 0);
        }
	}
	Dialog.output("reset");
}
