int clearCache(){
	//bsv
	remove("buf.bsv");
	//popup history
	remove(_data_dir"buf.bsv");
	//query
	remove("buf.csv");
	remove("buf2.csv");
	//script
	remove("buf.dat");
	remove("out.dat");
	//table
	remove("buf_table.dat");
	remove(_data_dir"buf_table.dat");
	return 0;
}
