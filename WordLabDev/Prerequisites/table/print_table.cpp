_table & _table::printtable(int LeftIndent,int TopIndent){
	if(TopIndent>=0) gotoxy(0,TopIndent);
	for(int r=0;r<getnumofrow();++r){
		// row border
		if(rows[r].getnumofcol()==1&&getwidth(r,0)==0){
			gotoxymove(0,LeftIndent,0,0);
			std::cout<<getkey(r,0)<<std::endl;
			continue;
		}
		// col border
		gotoxymove(0,LeftIndent,0,0);
		std::cout<<rows[r].getcolborder();
		// col item
		for(int c=0;c<rows[r].getnumofcol();++c){
			std::cout<<" "<<std::setw(getwidth(r,c))
			<<std::setiosflags(std::ios::left)<<getdata(r,c)// print to screen
			<<rows[r].getcolborder();
		}
		std::cout<<std::endl;
	}
	return *this;
}
