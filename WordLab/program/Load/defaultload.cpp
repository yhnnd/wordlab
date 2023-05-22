int load::defaultsLoad(const vector<string> msgs, int i, ...) {
    va_list argv;
    va_start(argv, i);

    while (i--) {
        const enum types type = va_arg(argv, enum types);
        const char * varName = va_arg(argv, char *);
        const string value = defaultSeek(msgs, varName);
		switch (type) {
            case types::Void: va_arg(argv, void *); break;
            case types::Bool: *va_arg(argv, bool *) = toBool(value); break;
			case types::Char: *va_arg(argv, char *) = toChar(value); break;
			case types::Int: *va_arg(argv, int *) = toInt(value); break;
            case types::Long: *va_arg(argv, long *) = toLong(value); break;
            case types::Short: *va_arg(argv, short *) = toShort(value); break;
            case types::Float: *va_arg(argv, float *) = toFloat(value); break;
            case types::Double: *va_arg(argv, double *) = toDouble(value); break;
            case types::String: *va_arg(argv, std::string *) = toString(value); break;
			default: va_arg(argv, void *); break;
        }
    }
    va_end(argv);
    return 0;
}
