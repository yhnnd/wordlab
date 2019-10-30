template <typename T> int toint(const T& object){
	int i;
	std::stringstream ss;
	ss<<object;
	ss>>i;
	return i;
}
