string Translation(int lth,int LineNumber) {
	int NOL=0;
	string line;
	ifstream fin;
	Library(fin,lth,CH);
	if(fin) {
		while(getline(fin,line)) {
			++NOL;
			if(NOL==LineNumber) { //LINE FOUND
				if(line.find("/redirected./")!=string::npos) { //LINE REDIRECTED
					string result_msg = ChineseRedirect(line,lth,LineNumber);
					if( lth>0 && LineNumber>0 ) return Translation(lth,LineNumber);
					else return result_msg;
				}
				// IF LINE HAS MULTIPLE ITEMS THEN SELECT ITEM
				int ATail = stroccurtimes(line.c_str(),"@");
				int ItemNumber = 1;
				if( auto_word_translation==false && ATail>1 ) {
					// SELECT ITEM
					ItemNumber = TranslationSelectItem(ATail,line,2,16,20,2);
				}
				fin.close();
				return TranslationGetItem(line.substr(lth),ItemNumber);
				break;
			}
		}
	} else {
		errorlog("Translation","cannot connect database",tostring(lth));
	}
	fin.close();
	return "";
}
