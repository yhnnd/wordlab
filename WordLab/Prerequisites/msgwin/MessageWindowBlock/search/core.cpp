int messageBlocks::SearchCore(const char what[][LINEMAX], const int max, const std::string keyword) {
	int r;
	for (r = 0; r < max; r++) {
        if (strcasestr(what[r], keyword.c_str()) != nullptr) {
            break;
        }
    }
	if (r == max) {
        return -1;
    }
	return r;
}
