template <typename arr2>
// copy this "<", ">", "(", ")", ";"
int bsvLinesGetMaxPlainTextCharLengthOfSingleLine (arr2 msgs, const size_t size, PKC brBegin, PKC brEnd, PKC fieldBegin, PKC fieldEnd, PKC term) {
    std::string::size_type maxLength = 0;
	for (size_t r = 0; r < size; ++r) {
        maxLength = std::max(maxLength, bsvLineGetPlainText(msgs[r], brBegin, brEnd, fieldBegin, fieldEnd, term).length());
    }
	return maxLength;
}
