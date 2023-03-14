string WLchinese(int lth,int number,int fontcolor) {
	string line;
	int NOL,redirect_times = 0;
	ifstream fin;
START:
	NOL = 0;
	Library(fin,lth,CH);
	while(!fin.eof()) {
		if(getline(fin,line)) ++NOL;
		if(NOL==number) {
			fin.close();
			if(fontcolor==2) return line.substr(0,lth);//Interface for Scan(A) engine
			else if(line.find("/redirected./")!=string::npos) {//Addon that support redirect definition
				++redirect_times;
				lth = number = 0;
				string redirect_result_msg = ChineseRedirect(line,lth,number);
				if( lth>0 && number>0 && redirect_result_msg=="" ) goto START;
				else return "<#red-ylw>( REDIRECT )<ylw-#red>( " + redirect_result_msg + " )";
			} else if(redirect_times) {
				return "<ylw-#red>( REDIRECT )" +
				       ( redirect_times>1 ? "<#red-ylw>( " + tostring(redirect_times) + " )" : "" )
				       + WLChineseCore(line.substr(lth),fontcolor);
			} else return WLChineseCore(line.substr(lth),fontcolor);//PLAIN DEFINITION
			break;
		}
	}
	fin.close();
	return "";
}
