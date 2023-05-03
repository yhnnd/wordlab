void SortDisplay(const char *keyword) {
	popup("sort of <ylw>(\"",
          keyword,
	      "\") is <-ylw>( ",
          sortOfWord(keyword),
	      " ) <-grn>( ",
          printableSortIdsOfWord(keyword),
	      " )",
          0);
}
