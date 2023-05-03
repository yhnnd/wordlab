std::string _table::makekey(){
	return toString(getnumofrow()) + "." + toString(colnow);
}
