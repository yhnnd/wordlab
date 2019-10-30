std::ostream & operator << ( std::ostream & os, _table & t){
	t.writetable(os);
	return os;
}
