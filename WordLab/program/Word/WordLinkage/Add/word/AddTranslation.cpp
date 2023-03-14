string AddWordGetTranslation(string word){
	// WARNING !
	// SHOULD AND MUST ONLY append word definitions to Chinese database
	// SHOULD NOT AND MUST NOT add endl or add word to Chinese database
	AddWordPrintMessage(3,word);// start editing definition
	string line_of_defs="",item_sort,item_trans;
	for(int i=0;;){// i is item NUMBER_OF_ORDER
		item_sort = AddWordGetSort();// select word sort item
	    if(item_sort.length()){
			AddWordPrintMessage(4,tostring(++i));// enter translation item
			cin>>item_trans;
			if( item_trans.length()>=2 ){
				AddWordPrintMessage(5,item_sort+" "+item_trans);//confirm definition item
				if(getch()==13){
					// append definition item to line_of_defs
					line_of_defs += (",/"+item_sort+"/@"+item_trans+";");
					AddWordPrintMessage(9,item_sort+" "+item_trans);// completed
				} else {
					AddWordPrintErrorMessage(9,item_sort+" "+item_trans);// deserted
				}
			}else{// trans.length < 2
				AddWordPrintErrorMessage(3);
				break;
			}
		}else{// no word sort
			AddWordPrintErrorMessage(2);
			break;
		}
		AddWordPrintMessage(6);// continue appending definitions ?
		if(getch()!=13) break;
	}
	AddWordPrintMessage(0);
	return line_of_defs;
}
