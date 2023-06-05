auto window::text::_alloc()->decltype(ptr) {
	if(!clear()) {
		errorLog("window.text.alloc", "error", "cannot clear memory");
	}
	ptr = (char**) calloc(capacity(),sizeof(char*));
	for(int i=0;i<capacity();i++){
		ptr[i] = (char*) calloc(linecapacity(),sizeof(char));
	}
	iscmd = (bool*) calloc(capacity(),sizeof(bool));
	return ptr;
}
