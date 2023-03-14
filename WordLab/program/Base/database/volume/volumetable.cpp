int VolumeTable(const string buf){//"buf_table.dat"
	if(buf.empty()) return 0;
	remove(buf.c_str());
	Volume(lang::EN,1,30,buf);
	int lth = 0, total = 0;
	for(lth = 1; lth <= 30; lth++) total += Volume(lang::EN,lth,lth,buf);
	Table.table(buf.c_str());
	return total;
}
