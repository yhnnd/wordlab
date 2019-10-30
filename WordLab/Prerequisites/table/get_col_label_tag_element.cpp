std::string & _table::getTagElement(int r,int c,int n){
	std::stringstream ss(getlabel(r,c));
	for(int i=0;i<=n;++i) ss>>data_str;
	return data_str;
}
//   0   1    2       3A       3B
// #pos row column ShowNull Readonly
