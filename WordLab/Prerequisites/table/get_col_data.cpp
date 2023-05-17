std::string & _table::getdata(int r,int c){
	std::stringstream ss(getlabel(r,c));
	ss >> data_str;
	// label is tag
	if( data_str == "#pos" ){
		int i = 0, coord[3] = {0,0,0};
		while ( ss>>data_str ) {
            coord[i++] = toInt(data_str);
        }
		int & r_data = coord[0], & c_data = coord[1],
		show_null = toInt(data_str[0]),
		readonly = toInt(data_str[1]);
		// tag have mapped data
		if(r_data<getnumofrowdata()&&c_data<data[i].getnumofcol()){
			if(readonly) {
                return data_str = data[r_data].getcol(c_data).text;
            } else {
                return data[r_data].getcol(c_data).text;
            }
		} else {// tag have no mapped data
            return data_str = show_null ? _table_null_data : "";
        }
	}
	return getlabel(r,c);
}
