int window::text::length(int n){
	return (n>=0 and n<capacity()) ? strlen(ptr[n]) : 0;
}
