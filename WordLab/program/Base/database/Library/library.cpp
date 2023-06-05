bool LibraryAdminValidate(const int lth,const lang LANG,const string admin,const string pwd){
	return admin==DatabaseAdminName && pwd==DatabaseAdminPassword;
}

FILE * Library(int lth,lang LANG,const string mode,const string admin="",const string pwd="") {
	FILE *fp = nullptr;
	string route = LibraryRoute(lth,LANG);
	if (mode.find("w") != std::string::npos && !LibraryAdminValidate(lth,LANG,admin,pwd)) {
        errorLog("library", "cannot rewrite", route);
	} else {
        fp=fopen(route.c_str(),mode.c_str());
    }
	if (fp == nullptr) {
        errorLog("library", "can not open", route);
    }
	return fp;
}

void Library(ifstream& fin,int lth,lang language){
	fin.open(LibraryRoute(lth,language));
}

// added on 2017.03.09
void Library(ofstream & fout,int lth,lang language){
	fout.open(LibraryRoute(lth,language),ios::app);
}
