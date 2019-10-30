std::string _table::makekey(){
	return tostring(getnumofrow())+"."+tostring(colnow);
}
