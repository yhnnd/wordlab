void _table::writedata( std::ostream & os ){
	for(int i=0;i<getnumofrowdata();++i){
		for(int j=0;j<data[i].getnumofcol();++j){
			os<<(j?" ":"")<<( data[i].getcol(j).text.length() ? data[i].getcol(j).text : "NULL");
		}
		os<<std::endl;
	}
}
void _table::writedata( std::string const & filename){
	std::ofstream fout(filename.c_str());
	writedata(fout);
	fout.close();
}
