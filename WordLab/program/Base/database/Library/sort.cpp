int sortlib(const int beginLth, const int endLth, const string admin, const string password) {
	int wordLth = 0, maxLines = 0;
	char **s_en = nullptr, **s_ch = nullptr;
	if (beginLth > endLth) {
        return sortLibError(-8);
    }
	for (wordLth = beginLth; wordLth <= endLth; wordLth++) {
		// validate
		if (!LibraryAdminValidate(wordLth, EN, admin, password)) {
            return sortLibError(-7, admin);
        }
		// read
		if ((maxLines = filelines(LibraryRoute(wordLth, EN), 1)) <= 0) {
            return sortLibError(-1);
        }
		if ((s_en = (char **)malloc(sizeof(char*) * maxLines)) == NULL) {
            return sortLibError(-2);
        }
		for (int r=0; r < maxLines; r++) {
            if ((s_en[r] = (char *)malloc(sizeof(char) * 32)) == NULL) {
                return sortLibError(-2);
            }
        }
		if ((s_ch = (char **)malloc(sizeof(char*) * maxLines)) == NULL) {
            return sortLibError(-2);
        }
		for (int r = 0; r < maxLines; r++) {
            if ((s_ch[r] = (char *)malloc(sizeof(char) * 256)) == NULL) {
                return sortLibError(-2);
            }
        }
		if (loadmsg(s_en, LibraryRoute(wordLth, EN), maxLines, 32, 1, 0) <= 0) {
            return sortLibError(-3);
        }
		if (loadmsg(s_ch, LibraryRoute(wordLth, CH), maxLines, 256, 1, 0) <= 0) {
            return sortLibError(-3);
        }
		// sort
		for (int r = 0; r < maxLines - 1; r++) {
			for (int j = r + 1; j < maxLines; j++) {
				if (compare(s_en[r], s_en[j], wordLth) > 0) {
                    strswap(s_en[r], s_en[j], 32);
                    strswap(s_ch[r], s_ch[j], 256);
				}
			}
		}
		// record
		FILE *fp_en = nullptr, *fp_ch = nullptr;
		if ((fp_en = fopen("lib_en.dat", "w")) == nullptr) {
            return sortLibError(-5);
        }
		if ((fp_ch = fopen("lib_ch.dat", "w")) == nullptr) {
            return sortLibError(-5);
        }
		for (int r = 0; r < maxLines; r++) {
			if (strncmp(s_en[r], s_ch[r], wordLth)) {
				sortLibError(-4, s_en[r]);
				continue;
			}
			fputs(s_en[r], fp_en);
			fputs(s_ch[r], fp_ch);
			if (r == maxLines - 1) {
                break;
            }
			fputc('\n', fp_en);
			fputc('\n', fp_ch);
		}
		fclose(fp_en);
		fclose(fp_ch);
		// rewrite
		remove(LibraryRoute(wordLth, EN).c_str());
		if (rename("lib_en.dat", LibraryRoute(wordLth, EN).c_str()) != 0) {
            return sortLibError(-6);
        }
		remove(LibraryRoute(wordLth, CH).c_str());
		if (rename("lib_ch.dat", LibraryRoute(wordLth, CH).c_str()) != 0) {
            return sortLibError(-6);
        }
		// free memory
		for (int r = 0; r < maxLines; r++) {
			free(s_en[r]);
			free(s_ch[r]);
		}
		free(s_en);
		free(s_ch);
	}
	string message= "from <ylw->(lth=" + toString(beginLth) + ") to <ylw->(lth=" + toString(endLth) + ")";
	return sortLibError(0, message);
}
