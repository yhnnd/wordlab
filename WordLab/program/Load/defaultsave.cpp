int load::defaultsSave(const char * route, int i, ...) {
    va_list argv;
    va_start(argv, i);

	ofstream fout(route, ios::out);
    while (i--) {
    	const enum types type = va_arg(argv, enum types);
        const string msg = va_arg(argv, char *);
        string value = "";
        //'bool' is promoted to 'int' when passed through '...'
        //'char' is promoted to 'int' when passed through '...'
        //'float' is promoted to 'double' when passed through '...'
        switch (type) {
            case types::Bool: value = toString(va_arg(argv, int)); break;
            case types::Char: value = toString(va_arg(argv, int)); break;
            case types::Int:  value = toString(va_arg(argv, int)); break;
            case types::Long: value = toString(va_arg(argv, long)); break;
            case types::Short: value = toString(va_arg(argv, int)); break;
            case types::Float: value = toString(va_arg(argv, double)); break;
            case types::Double: value = toString(va_arg(argv, double)); break;
            case types::String: value = va_arg(argv, const char *); break;
            default: va_arg(argv, void *); break;
        }
		fout << msg << this->delimiter << value << endl;
    }
    fout.close();

    va_end(argv);
    return 0;
}
