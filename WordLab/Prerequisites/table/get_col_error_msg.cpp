const std::string _table::geterror(int r,int c){
	std::string msg = getlabel(r,c);
	if (msg==_table_label_out_of_range) {
        return "OUT OF RANGE";
    }
	if (msg==_table_null_label) {
        return "NOT A LABEL";
    }
	msg = getdata(r,c);
	if (msg==_table_null_data) {
        return "DATA NOT FOUND";
    }
	return "";
}
