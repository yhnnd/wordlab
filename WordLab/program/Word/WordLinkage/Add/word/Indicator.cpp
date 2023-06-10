void AddWordPrintMessage(int r,const string s = "") {
	switch (r) {
		case  0:  Dialog.output("DEFINITION EDITING COMPLETED");              break;
		case  1:  Dialog.output("ADD WORD \"" + s + "\" ?");                  break;
		case  2:  Dialog.output("CONFIRM ?");                                 break;
		case  3:  Dialog.output("EDITING DEFINITION OF " + s);                break;
		case  4:  Dialog.output("ENTER TRANSLATION NO." + s);                 break;
		case  5:  Dialog.output("APPEND DEFINITION " + s + " ?");             break;
        case  6:  Dialog.output("ADD PHRASE \"" + s + "\" ?");                break;
		case  7:  Dialog.output("WORD SORT \"" + s + "\" SELECTED");          break;
		case  8:  Dialog.output("ADD \"" + s + "\" ?");                       break;
		case  9:  Dialog.output("EDITING OF DEFINITION ITEM "+s+" COMPLETED");break;
		default:  break;
	}
}

void AddWordPrintErrorMessage(int r,const string s=""){
	switch (r){
	    case  1:  Dialog.output("ADDITION CANCELLED",lightred); break;
	    case  2:  Dialog.output("DEFINITION EDITING CANCELLED FOR NO WORD SORT",lightred); break;
	    case  3:  Dialog.output("DEFINITION EDITING CANCELLED FOR TRANSLATION IS TOO SHORT",lightred); break;
		case  4:  Dialog.output("ERROR: DATABASE NOT AVAILABLE",lightred); break;
	    case  5:  Dialog.output("WORD SORT SELECTING CANCELLED",lightred); break;
	    case  6:  Dialog.output("WORD SORT EDITING CANCELLED",lightred); break;
	    case  7:  popup("<ylw->(",s,") IS IN THE DATABASE ALREADY",0); break;
		case  8:  Dialog.output("WORD ADDITION CANCELLED BECAUSE OF NO DEFINITION",lightred); break;
		case  9:  Dialog.output("WORD DEFINITION ITEM " + s + " DESERTED",lightred); break;
		default:  Dialog.output("UNKNOWN ERROR "+toString(r),lightred); break;
	}
}
