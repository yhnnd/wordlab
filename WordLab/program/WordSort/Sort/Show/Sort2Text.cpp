const char *getWordSortNameById(const int n) {
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
			return "conjunction";
			break;
		case 11:
            return "article";
			break;
        case 12:
            return "interjection";
            break;
        case 13:
            return "numeral";
            break;
        case 14:
            return "countable";
            break;
        case 15:
            return "uncountable";
            break;
        case 16:
            return "single";
            break;
        case 17:
            return "plural";
            break;
        case 18:
            return "abbreviation";
            break;
        case 19:
            return "prefix";
            break;
        case 20:
            return "postfix";
            break;
		default:
			return "Unknown";
			break;
	}
	return "error";
}
