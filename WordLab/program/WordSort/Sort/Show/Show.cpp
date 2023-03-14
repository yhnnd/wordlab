void SortDisplay(const char *keyword) {
	popup("sort of <yellow>(",keyword,
	      ") is <back yellow>(",sortofword(keyword),
	      ")<back green>(",tostring(WordSort(keyword)),
	      ")",0);
}
