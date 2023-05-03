void findinfile(string msg,string filename,string buf) {
	string msgfile;
	ifstream fin(filename);
	if (fin.fail()) {
		errorlog("find reverse","error opening",filename);
		return;
	}
	while (!fin.eof()) {
		getline(fin,msgfile);
		auto p = msgfile.find(msg);
		if (p != std::string::npos) {
		    ofstream fout(buf,ios::out|ios::app);
			fout << msgfile.substr(0,p);
			fout << "<-ylw>(" << msgfile.substr(p,msg.length()) <<")";
			fout << msgfile.substr(p+msg.length());
            fout << endl;
			fout.close();
		}
	}
	fin.close();
}
