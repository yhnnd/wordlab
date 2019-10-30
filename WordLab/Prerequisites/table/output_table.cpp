void _table::writetable( std::ostream & os ){
	for(int r=0;r<getnumofrow();++r){
		// row border
		if(rows[r].getnumofcol()==1&&getwidth(r,0)==0){
			os<<getkey(r,0)<<std::endl;
			continue;
		}
		// col border
		os<<rows[r].getcolborder();
		// col item
		for(int c=0;c<rows[r].getnumofcol();++c){
			os<<" "<<std::setiosflags(std::ios::left)<<std::setw(getwidth(r,c));
			os<< getkey(r,c);// write to file
			os<<rows[r].getcolborder();
		}
		os<<std::endl;
	}
}
void _table::writetable(std::string const & filename){
	std::ofstream fout(filename.c_str());
	writetable(fout);
	fout.close();
}
