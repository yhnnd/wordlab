int querybetween(string msg){
	int offset=3;
	querynext(msg);
	queryfrom();
	querynext(msg.substr(msg.find("and ")+4));
	queryto();
	attr_n++;
	return offset;
}
