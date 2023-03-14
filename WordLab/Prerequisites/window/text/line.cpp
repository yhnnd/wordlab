char * window::text::line(int n) {
	return (n>=0 and n<capacity()) ? ptr[n] : nullptr;
}
