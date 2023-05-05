void SortDisplay(const char *keyword) {
	popup("sort of <ylw-blk>(\"",
          keyword,
	      "\") is <blk-ylw>( ",
          replace(sortOfWord(keyword), ",", " /"),
	      " ) <blk-grn>( ",
          replace(printableSortIdsOfWord(keyword), ",", ""),
	      " )",
          0);
}
