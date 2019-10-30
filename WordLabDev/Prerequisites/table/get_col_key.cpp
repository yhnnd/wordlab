std::string & _table::getkey(int r,int c){
	if(r<getnumofrow()&&c<rows[r].getnumofcol()){
		return rows[r].getcol(c).text;
	}
	return data_str = _table_key_out_of_range;
}
