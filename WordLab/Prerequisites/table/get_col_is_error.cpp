const bool _table::iserror(int r,int c){
	const std::string temp_label_str = getlabel(r,c);
	if (temp_label_str == _table_label_out_of_range || temp_label_str == _table_null_label) {
        return 1;
    }
	const std::string temp_data_str = getdata(r,c);
	if (temp_data_str == _table_null_data) {
        return 1;
    }
	return 0;
}
