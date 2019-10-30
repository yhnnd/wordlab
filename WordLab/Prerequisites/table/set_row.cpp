//can ONLY used in situation that the nearest row above is a border row
//and this row has ONLY one column
_table & _table::setrow(std::string text){
	int nRow = getnumofrow();
	if(nRow<1||getwidth(nRow-1,0)) return *this;
	int width=getrow(getnumofrow()-1).getcol(0).text.length()-3;
	setrow(1);
	setcol(width,text);
	return *this;
}

_table & _table::setrow(int numofcol){
	colnow=0;
	colmax=numofcol;
	return *this;
}

_table & _table::setrow(int colwidth,std::string coltext){
	setrow(1);
	setcol(colwidth,coltext);
	return *this;
}
