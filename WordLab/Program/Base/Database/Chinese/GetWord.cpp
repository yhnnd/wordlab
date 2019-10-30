string GetWord(int lth,int lineNumber){
	int NOL=0;
	string line,def;
	ifstream fin;
	Library(fin,lth,lang::CH);
	while(!fin.eof()){
		if(getline(fin,line)) NOL++;
		if(NOL==lineNumber){
			def=line.substr(0,lth);
		    break;
		}
	}
	fin.close();
	return def;
}
