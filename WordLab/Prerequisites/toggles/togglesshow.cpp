void togglesShow(const int x, const int y, const int width, const bool showDigit, const int n, ...) {
	int r;
    va_list argv;
    va_start(argv, n);
	for (r = 1; r <= n; r++) {
        toggleShow(x + width, y + 1 + r, va_arg(argv, int), false, showDigit);
    }
    va_end(argv);
}
