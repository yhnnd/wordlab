int strindex(const char *str, const char *substr) {
	const char * index = strstr(str,substr);
	if( index != nullptr ) {
        return index - str;
    }
	return -1;
}
