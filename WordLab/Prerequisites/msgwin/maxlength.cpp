int MaxLength(const char *what,int width){
	int r;
	for (r = 0; *(what+r*width) != 0; r++) {
    }
	return r;
}

int MaxLength(const char *what,int max,int width){
	int r;
	for (r = 0; r < max && *(what+r*width) != 0; r++) {
    }
	return r;
}
