int queryselect() {
	int n=0,l=0,i=0,j=0,nbuf=0;
	string ln;
	ifstream fin;
	ofstream fout;
	for(n=0; n<attr_n; n++) {
		if(attr[n].name=="lth") {
			fout.open("buf.csv",ios::trunc);
			int lthfrom=stoi(attr[n].value.from);
			int lthto=stoi(attr[n].value.to);
			for(l=lthfrom; l<=lthto; l++) {
				Library(fin,l,CH);
				while (getline(fin,ln)) {
					fout << ln << ", $lth=" << l << ", $n=" << i++ << endl;
				}
				fout << endl;
				fin.close();
			}
			fout.close();
			nbuf++;
		}
	}
	for(n=0; n<attr_n; n++) {
		if(attr[n].name=="sort") {
			attr[n].value.surround(0,"[","]");
			if(nbuf%2) {
				fin.open("buf.csv");
				fout.open("buf2.csv",ios::trunc);
			} else {
				fin.open("buf2.csv");
				fout.open("buf.csv",ios::trunc);
			}
			while(getline(fin,ln)) {
				if(ln.find(attr[n].value.self)!=std::string::npos) {
                    fout << ln << endl;
                }
			}
			fin.close();
			fout.close();
			nbuf++;
		}
	}
	for(n=0; n<attr_n; n++) {
		char pattern=0;
		if(attr[n].name=="word"||attr[n].name=="value"
		        ||attr[n].name=="text") pattern=1;
		else if(attr[n].name=="affix"||attr[n].name=="substr"
		        ||attr[n].name=="index") pattern=2;
		else if(attr[n].name=="prefix"||attr[n].name=="begin"
		        ||attr[n].name=="start") pattern=3;
		else if(attr[n].name=="suffix"||attr[n].name=="end"
		        ||attr[n].name=="postfix") pattern=4;
		else if(attr[n].name=="infix"||attr[n].name=="inside"
		        ||attr[n].name=="mid") pattern=5;
		else if(attr[n].name=="regex"||attr[n].name=="match"
		        ||attr[n].name=="pattern"||attr[n].name=="like") pattern=6;
		else if(attr[n].name=="contains"||attr[n].name=="subset"
		        ||attr[n].name=="strorder") pattern=7;
		if(pattern>0) {
			if(nbuf%2) {
				fin.open("buf.csv");
				fout.open("buf2.csv",ios::trunc);
			} else {
				fin.open("buf2.csv");
				fout.open("buf.csv",ios::trunc);
			}
			l = attr[n].value.self.length();
			while(getline(fin,ln)) {
				i=ln.find(attr[n].value.self);
				j=ln.find(" ");
				if(	(pattern==6&&match(ln.substr(0,j+1),attr[n].value.self+" "))
				        ||	(pattern==7&&strHasSubseq(ln.substr(0,j+1),attr[n].value.self+" "))
				        ||	(	(i!=std::string::npos)
				                &&	((pattern==1&&i==0&&i+l==j)
				                     ||(pattern==2&&i>=0&&i<j)
				                     ||(pattern==3&&i==0)
				                     ||(pattern==4&&i+l==j)
				                     ||(pattern==5&&i>0&&i+l<j))
				           ))
					fout<<ln<<endl;
			}
			fin.close();
			fout.close();
			nbuf++;
		}
	}
	Table.table((nbuf % 2) ? "buf.csv" : "buf2.csv", 0, 0, ScreenX - 6);
    return 0;
}
