_table & _table::setcolborder(char c){
	for(int i=0;i<getnumofrow();++i) rows[i].setcolborder(c);
	return *this;
}
