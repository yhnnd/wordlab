// copy this "<", ">", "()", ";"
int bsvmaxlth(PKC msg,PKC brBegin,PKC brEnd,PKC omit,PKC term) {
	int r, lth;
	for (r = 0, lth = 0; strchr(term,msg[r]) == nullptr && msg[r] != '\0'; r++) {
		if (strchr(brBegin, msg[r])) {
            for (r++; !strchr(brEnd, msg[r]); r++) {

            }
        } else if (strchr(omit,msg[r])) {

        } else {
            lth++;
        }
	}
	return lth;
}
