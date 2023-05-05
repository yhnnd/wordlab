int messageblock::SearchCore(const char what[][LINEMAX], int max, char *keyword) {
	int r;
	for (r = 0; r < max; r++) {
        if (strcasestr(what[r],keyword) != nullptr) {
            break;
        }
    }
	if (r == max) {
        return -1;
    }
	return r;
}
