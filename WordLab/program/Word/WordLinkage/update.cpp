char WordUpdate(const string word){
	const int lth = word.length(), n = Search(word.c_str(), lth, false);
	if (n <= 0) {
		popup(word," was not in the database, please add it first",-1);
		return 0;
	}
	char trans[256],route[64];
	FILE *fp = Library(lth,CH,"r");
	for (int i = 1; i <= n; i++) {
        fgets(trans, 256, fp);
    }
	fclose(fp);
	const int i = strindex(trans, "\n");
	if (i >= 0) {
        trans[i] = 0;
    }
	Dialog.output("start");
	for(;;){
		Dialog.output(trans,light|yellow);//print definition
	    listen(trans,strlen(trans),1,{13,0,EOF},256);//edit definition
	    Dialog.output(string("use (")+trans+")?",lightyellow);
        const char ch = getch();
	    if (ch == 13 || ch == 10) {
            break;
        }
	}
    if (DeleteLine(LibraryRoute(lth,EN),n,1) != 0) {
	    popup("cannot delete word <red-blk>(",word,")",-1);
		return 0;
	}
	if (DeleteLine(LibraryRoute(lth,CH),n,1) != 0) {
	    popup("cannot delete definition of <red-blk>(",word,")",-1);
		return 0;
	}
	//add word to English database
    ofstream fout, flog;
	Library(fout,lth,EN);
	fout<<endl<<word;
    fout.close();//close db-en
    //add word and definition to chinese database
    Library(fout,lth,CH);
    fout<<endl<<trans;
    //write log file 1
    flog.open(UpdateWordLog,std::ios::app);
    flog<<"<time>"<<getCurrentTime()<<endl;
    flog<<"<word>"<<word<<endl;
    flog<<"<defs>"<<trans;//will be followed by new definitions
    //add more definition to chinese database
    Dialog.output("add new definition?");
    const char ch = getch();
    if (ch == 13 || ch == 10) {
		string trans_new = AddWordGetTranslation(word);//exprimt'l
		if(trans_new.length()>5/*/n./{};*/){
			Dialog.output("add \""+trans_new+"\" ?");
            const char ch = getch();
			if (ch == 13 || ch == 10) {
				fout << trans_new;
    			flog << trans_new << "\n" << endl;//write log file 2
			}else Dialog.output("cancelled");
		}else Dialog.output("cancelled");
	}
    fout.close();//close db-zh
    flog.close();//close log file
    //sort words in db-lth
	sortlib(lth,lth,DatabaseAdminName,DatabaseAdminPassword);
    popup("updating of <ylw-blk>(",word,") is completed",0);
    {
        const char ch = wait(-1, 100, 0);
        Dialog.output("reset");
        return ch;
    }
}
