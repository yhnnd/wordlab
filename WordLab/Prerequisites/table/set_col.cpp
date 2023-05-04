_table & _table::setcol(int colwidth,std::string coltext){
	if(colnow<colmax){
		std::string key = makekey();
		rowtemp.setcol(colwidth,key);
		labels[ key ] = coltext;
		if(++colnow==colmax){
			rows.push_back(rowtemp);
			rowtemp.clear();
			colmax=0;
		}
	}else colmax=0;
	return * this;
}

_table & _table::setcol(std::string coltext) {
	int width = 0;
	if( colnow<getrow(getnumofrow()-1).getnumofcol() ){
		width = getwidth(getnumofrow()-1,colnow);
	}
	if( width == 0 ) width = getwidth(getnumofrow()-2,colnow);
	return setcol(width,coltext);
}
