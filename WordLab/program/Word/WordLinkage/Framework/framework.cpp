int WLFramework() {
	int lth = 0;
    char s[32] = "", FirstLetter = 0;
	if( VL and db_is_secure(false,true)==false ) wl_getch();
	if(Ctype==0) {
		if(popup("<-wte>(Add word Engine Authorization Was Set Off. Reset now?",-1) == WL_KEY_ENTER) {
			Ctype = 1;
		}
	}
	colorset(white);
#ifdef _WIN32
	system("cls");
	for(;;) {
        // INPUT DATA
		if(FirstLetter!=13) {
			memset(s,0,sizeof(s));
			if(isalpha(FirstLetter)) s[0] = FirstLetter;
			indexCore(s,10,9,light|green);
			index(s,10,9,light|green,isalpha(FirstLetter)?1:0);
			FirstLetter = 0;
			lth=strlen(s);
		}
		// PROCESS DATA
		char * ptr_token=strstr(s,"#");
		if(ptr_token!=nullptr) {
			(*ptr_token)=0;//remove #
			if(*(ptr_token+1)!='\0') strcpy(ptr_token,ptr_token+1);
			//re-order the word after removing #
			FirstLetter = WLTools(s)? 13 : 0;
		} else if(strindex(s," ")>=0) {
			if(!WLSearchPhrase(s)&&CL) AddNew(s);
		} else if(lth<=0||lth>30) {
            return -1;
        } else {
			int BeginY = 5;
			clearscreen(0,BeginY,ScreenX,ScreenY-1-BeginY);
			gotoxy(0,BeginY);
			FirstLetter = WLFrameworkCore(s);
			FirstLetter = WLDictionary(s);
			if( FirstLetter == 8 || FirstLetter == 27 ) return -1;
			// (BELOW) PREVENT FROM CLEARSCREEN IMMEDIATELY
			else if(!isalpha(FirstLetter)) FirstLetter = wl_getch();
			if( FirstLetter == 8 || FirstLetter == 27 ) return -1;
		}
	}
#elif __APPLE__
    for (;;) {
        cout << endl << "Search:";
        cin >> s;
        lth = strlen(s);
        std::ifstream entry_lib_lth(LibraryRoute(lth, EN));
        if (entry_lib_lth.is_open()) {
            std::ifstream defs_lib_lth(LibraryRoute(lth, CH));
            if (defs_lib_lth.is_open()) {
                std::string line_entry, line_defs;
                unsigned short matchedCount = 0;
                while (entry_lib_lth && defs_lib_lth) {
                    std::getline(entry_lib_lth, line_entry);
                    std::getline(defs_lib_lth, line_defs);
                    if (line_entry == s) {
                        ++matchedCount;
                        std::cout << line_entry << " => " << line_defs << endl;
                    }
                }
                defs_lib_lth.close();
                if (matchedCount > 0) {
                    cout << matchedCount << " results found." << endl;
                } else {
                    cout << "No result." << endl;
                }
            }
            entry_lib_lth.close();
        }
    }
#endif
}
