struct history {
	void writer(PKC route, PKC title, const std::string msg, int n);
	void RecordSearch(const std::string msg, const int n);
	void RecordAnswer(const std::string msg, const int n);
	void RecordUnfound(const std::string msg, const int n);
	void deleteFile(const std::string route, const std::string title);
	void clear();
	void read(const char *, const char *);
} WLHistory;


void history::writer(PKC route, PKC title, const std::string msg, const int n) {
    status(title, ": Checking (", msg, ");");
    if (findReverse(msg.c_str(), route)) {
        return;
    }
    status(title, ": Recording (", msg, ");");
    ofstream fout(route, ios::app);
    fout << "0 " << msg << ",$n=" << n << endl;
    fout.close();
}


void history::RecordSearch(const string msg, const int n) {
    writer(SearchHistory,"Search History", msg, n);
}

void history::RecordAnswer(const string msg, const int n) {
    writer(AnswerHistory,"Answer History", msg, n);
}

void history::RecordUnfound(const string msg, const int n) {
    writer(UnknownHistory,"Unknown History", msg, n);
}


void history::deleteFile(const std::string route, const std::string title) {
    FILE *fp = NULL;
    if ((fp = fopen(route.c_str(), "r")) == NULL) {
        popup("<ylw-blk>(", title, ") already deleted;", 0);
        return;
    }
    fclose(fp);

    remove(route.c_str());

    if ((fp = fopen(route.c_str(), "r")) == NULL) {
        popup("<ylw-blk>(", title, ") deleted;", 0);
    } else {
        popup("unable to delete <ylw-blk>(", title, ");", -1);
    }
    fclose(fp);
}


void history::clear() {
    deleteFile(SearchHistory, "SEARCH HISTORY");
    deleteFile(AnswerHistory, "ANSWER HISTORY");
    deleteFile(UnknownHistory, "UNKNOWN HISTORY");
}


void history::read(const char *route, const char *title) {
    FILE * fp = NULL;
    if ((fp = fopen(route,"r")) == NULL) {
        popup("<ylw->(", title, ") HAS BEEN DELETED;", 0);
    } else {
        Table.table(route);
    }
    fclose(fp);
}
