void messageBlocks::FillAll(const char what[][LINEMAX], const int nPrev, const int n, const int max) {

	recordColor(colorprev, "FillAll");

	for (int r= (nPrev <= n) ? 1 : max - 1;
         ((nPrev <= n) && (r < max)) || (!(nPrev <= n) && (r >= 1));
	        r= (nPrev <= n) ? r + 1 : r - 1) {
		if (n == nPrev) {
            Fill(what[r], getBlockPos(r), r, r - n);// initiate
        } else if (r == nPrev) {
            Fill(what[r], getBlockPos(r), r, r - n);// previous
        } else if (r == n) {
            Fill(what[r], getBlockPos(r), r, r - n);// present
        }
	}

    if (n >= 0 && n < max) {
        printBlockContent(x, y - 2, width, what[n]);
    } else {
        printBlockContent(x, y - 2, width, "");
    }

    resetColor(colorprev, "FillAll");
}
