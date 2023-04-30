int maths::filter(int n, int *flags, int *length) {
	int r;
	for(r = 0; r < *length; r++) {
        if(flags[r] == n) {
            return r;
        }
    }
    flags[r++] = n;
	*length = r;
	return 0;
}
