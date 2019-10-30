_table & _table::setrowborder(int width,char line,char cross){
	std::stringstream ss;
	std::string border_str;
	if(width){
		ss<<cross<<std::setw(width)<<std::setfill(line)<<""<<cross;
		goto Load;
	}else{// width == 0
		if(rows.size()==0) return *this;
		for(int i=0;i<rows[rows.size()-1].getnumofcol();++i){
			ss<<cross<<std::setw(rows[rows.size()-1].getcol(i).width+1)<<std::setfill(line)<<"";
		}
		ss<<cross;
	}
	Load:
	getline(ss,border_str);
	_tablerow rowTemp;
	rowTemp.setcol(0,border_str);
	rows.push_back(rowTemp);
	return *this;
}
