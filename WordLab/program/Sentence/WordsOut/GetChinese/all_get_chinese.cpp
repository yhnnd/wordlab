int sts::getChineseOfWord(const char *s, char * def, const size_t size) {
    memset(def, 0, size);
	char c[32] = "";
	int r, k, km, number = 0, lth = strlen(s);
	FILE * fp = Library(lth, EN, "r");
	int NOL = fileLines(fp, false);
	for (k = 1; k <= NOL; k++) {
		fseek(fp, (k - 1) * (lth + 1), 0);
		fread(&c, lth, 1, fp);
		rewind(fp);

        if (strlen(c) != lth) {
            printf("getChineseOfWord: db damaged at k = %d c = \"%s\"\n", k, c);
            break;
        }

		for (km = 0, r = 0; r < lth; r++) {
            if (s[r] == c[r]) {
                km = km + 1;
            }
        }
		if (km == lth) {
            const int result = Translation(lth, k, def, size);
            if (result > 0) {
                number = 1;
            }
			break;
		}
	}
	fclose(fp);
	return number;
}


int sts::getChineseOfWord_S(const char *s, char * def, const size_t size, const int Limit) {
    memset(def, 0, size);
	char c[32] = "";
	int r, k, km, number = 0, lth = strlen(s);
	FILE * fp = Library(lth, EN, "r");
	int NOL = fileLines(fp, false);
	for(k = 1; k <= NOL; k++) {
		fseek(fp, (k - 1) * (lth + 1), 0);
		fread(&c, lth, 1, fp);
		rewind(fp);

        if (strlen(c) != lth) {
            printf("getChineseOfWord: db damaged at k = %d c = \"%s\"\n", k, c);
            break;
        }

		for (km = 0, r = 0; r < lth; r++) {
            if (s[r] == c[r]) {
                km = km + 1;
            }
        }
		if (km >= lth - Limit) {
            const int result = Translation(lth, k, def, size);
            if (result > 0) {
                number++;
            }
			break;
		}
	}
	fclose(fp);
	return number;
}

int sts::printChineseOfWord(const char *word, const int limit) {
    const size_t size = 64;
    char * def = (char *) calloc(size, sizeof(char));
    if (def == nullptr) {
        return 0;
    }
    int result = 0;
    if (limit == 0) {
        result = getChineseOfWord(word, def, size * sizeof(char));
    } else {
        result = getChineseOfWord_S(word, def, size * sizeof(char), limit);
    }
    if (result > 0) {
        printf("%s", def);
        return result;
    }
    return 0;
}