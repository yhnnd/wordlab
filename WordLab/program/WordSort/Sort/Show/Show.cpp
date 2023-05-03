void SortDisplay(const char *keyword) {
	popup("sort of <ylw>(\"",
          keyword,
	      "\") is <-ylw>( ",
          sortofword(keyword),
	      " ) <-grn>( ",
          toString(WordSort(keyword)),
	      " )",
          0);
}
