int Search(const char *s, int lth, const bool ignoreCase) {
	char c[32];

    if (lth <= 0) {
        lth = strlen(s);
    }

	FILE * fp = Library(lth, EN, "r");

	if (fp == nullptr) {
        return -1;//Xprmt'l updated on 2017.03.14
    }

	int k = 0, kprev[36], kn = 0, a = 0, z = 0, number = 0, n = filelines(fp, 0), flag = 0;

	for (a = 1, z = n; (a < z && (a == 1 || z == n)) || (a < z - 1 && a > 1 && z < n); ) {
        if (flag > 0) {
            k = a + ceil((z - a) / 2.0);
        } else {
            k = a + floor((z - a) / 2.0);
        }

		if (maths::filter(k, kprev, &kn)) {
            break;
        }

		fseek(fp, (k - 1) * (lth + 1), 0);
		fread(&c, lth, 1, fp);
		rewind(fp);

        if (ignoreCase == true) {
            flag = strnicmp(s, c, lth);
        } else {
            flag = strncmp(s, c, lth);
        }

		if (flag < 0) {
            z = k;
        } else if (flag > 0) {
            a = k;
        } else {
			number = 1;
			break;
		}
	}
	fclose(fp);
	return number * k;
}
