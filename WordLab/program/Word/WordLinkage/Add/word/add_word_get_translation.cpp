string AddWordGetTranslation(string word) {
    const vector<string> msgs = {"", "", "", "    continue appending definitions ?", "", "", "", "", ""};
    const int x = 20, y = 8, width = 40;
	// WARNING !
	// SHOULD AND MUST ONLY append word definitions to chinese database
	// SHOULD NOT AND MUST NOT add endl or add word to chinese database
	AddWordPrintMessage(3, word);// start editing definition
	string line_of_defs = "", item_sort = "", item_trans = "";
	for(int i = 0;;){// i is item NUMBER_OF_ORDER
		item_sort = AddWordGetSort(x, y + 1, width);// select word sort item
	    if (item_sort.length()) {
			AddWordPrintMessage(4, toString(++i));// enter translation item

            ::fflush(stdin);
            cin.clear();
            cin.sync();

			std::getline(cin, item_trans);

			if (item_trans.length() >= 2) {
				AddWordPrintMessage(5, "/" + item_sort + "/ \"" + item_trans + "\"");// confirm definition item

                ::fflush(stdin);
                cin.clear();
                cin.sync();

				const char ch = getch();
//                printf("\nyou pressed '%c' (%d)\n", ch, ch);
				if (ch == 13/* Windows ENTER */ || ch == 10/* Mac OS ENTER */) {
					// append definition item to line_of_defs
					line_of_defs += (",/" + item_sort + "/@" + item_trans + ";");
//                    cout << "17. line_of_defs += \"" << (",/" + item_sort + "/@" + item_trans + ";") << "\"\n";
//                    cout << "18. line_of_defs = \"" << line_of_defs << "\"";
//                    getch();
					AddWordPrintMessage(9, item_sort + " " + item_trans);// completed
				} else {
					AddWordPrintErrorMessage(9, item_sort + " " + item_trans);// deserted
				}
			} else {// trans.length < 2
				AddWordPrintErrorMessage(3);
				break;
			}
		} else {// no word sort
			AddWordPrintErrorMessage(2);
			break;
		}
        const int choice = MessageWindow.Confirm(2, x, y, width, msgs);
		if (choice != 1) {
			break;
		}
	}
	AddWordPrintMessage(0);
//    cout << "38. line_of_defs = \"" << line_of_defs << "\"";
//    getch();
	return line_of_defs;
}
