const char *sortofword(const int n) {
	switch (n) {
		case 0:
			return "no type";
			break;
		case 1:
			return "noun";
			break;
		case 2:
			return "verb";
			break;
		case 3:
			return "adjective";
			break;
		case 4:
			return "adverb";
			break;
		case 5:
			return "transitive verb";
			break;
		case 6:
			return "intransitive verb";
			break;
		case 7:
			return "preposition";
			break;
		case 8:
			return "pronoun";
			break;
		case 9:
			return "auxil";
			break;
		case 10:
			return "conjuction";
			break;
		case 11:
			return "article";
			break;
		default:
			return "Unknown";
			break;
	}
	return "error";
}
