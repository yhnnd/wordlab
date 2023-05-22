// r is the NO. of the toggle, n is the maximum of toggles
void toggles(int x,int y,int width,bool showdigit,int r,int n,...) {
	if (r < 0 || r > n) return;
	int i;
	bool * flagptr = NULL;
	va_list argv;
	va_start(argv,n);
	for(i = 1; i <= r && i <= n; i++) {
		flagptr = va_arg(argv,bool *);
	}
	va_end(argv);
	toggle(x + width, y + 1 + r, flagptr, true, showdigit);
}
