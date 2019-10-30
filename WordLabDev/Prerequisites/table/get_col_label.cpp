std::string & _table::getlabel(std::string key){
	return labels.find(key) == labels.end() ? data_str = _table_null_label : labels[ key ];
}
std::string & _table::getlabel(int r,int c){
	if(r<getnumofrow()&&c<rows[r].getnumofcol())
	return getlabel( tostring(r)+"."+tostring(c) );
	else return data_str = _table_label_out_of_range;
}
