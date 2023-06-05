bool db_is_secure(const bool print_success, const bool print_error){
	int lth = 0, nol[2] = {0,0}, error = 0;
	// check if db-en-lth.nol equals db-zh-lth.nol
	status("db error locater is running");
	for(lth = 1; lth <= 30; ++lth ){
		nol[lang::EN] = Volume(lang::EN,lth,lth,"");
		nol[lang::CH] = Volume(lang::CH,lth,lth,"");
		if( nol[lang::EN] != nol[lang::CH] ) break;
	}
	// check db-en/zh accordance and db-zh's syntax
	status("db woodpecker is running");
    error += WoodPeckerCheckCongruence(1,30);
    error += WoodPeckerCheckSyntax(1,30,256);
    // exception
    if( error < 0 ){
        errorLog("woodpecker", "data file lost");
		return false;
	}
    // summary
	if( lth == 31 and error == 0 ){
		if(print_success) {
            popup("all functions <grn->(SECURE)", 0);
        }
		return true;
	} else {
		if(print_error){
			popup(string("<-red>( database damaged )<-ylw>( lth\\(")+toString(lth)
			+"\\) line\\("+toString(nol[lang::EN])+"\\) error\\("+toString(error)+"\\)",0);
		}
		return false;
	}
}
