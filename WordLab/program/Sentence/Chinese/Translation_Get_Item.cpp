string TranslationGetItem(string line,int ItemNumber) {
	// IF ITEM NOT FOUND THEN RETURN "NULL"
	// ITEM_NUMBER DEFAULT IS 1
	int i=0,CurrentItemNumber=0;
	bool InItemTranslation=false,InItemTranslationComment=false;
	for(i=0,CurrentItemNumber=0; i<line.length()&&CurrentItemNumber<ItemNumber; ++i) {
		if(line[i]=='@') {
			if(InItemTranslation==false) {
				//Begin of Item Translation
				InItemTranslation=true;
				++CurrentItemNumber;
			} else {
				//End of Item Translation
			}
		}
		if(line[i]==';') InItemTranslation=false;
	}
	if(i<line.length()&&CurrentItemNumber==ItemNumber) { //Item Found
		string print_msg = "";
		for(; i<line.length(); ++i) {
			if(line[i]=='\n'||line[i]==0) break;
			else if(line[i]=='@'||line[i]==';') break;
			else if(strchr("([<",line[i])) InItemTranslationComment=true;
			else if(strchr(")]>",line[i])) InItemTranslationComment=false;
			else if(!InItemTranslationComment) print_msg += line[i];
		}
		return print_msg;
	}
	return "NULL";
}
