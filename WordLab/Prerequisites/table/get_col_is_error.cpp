const bool _table::iserror(int r,int c){
	data_str = getlabel(r,c);
	if(data_str==_table_label_out_of_range
	||data_str==_table_null_label) return 1;
	data_str = getdata(r,c);
	if(data_str==_table_null_data) return 1;
	return 0;
}
