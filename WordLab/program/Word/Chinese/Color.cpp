string getChineseColorCommandByNumber(int d) {
	if (d == 0) {
        return "grn-";//GREEN
    } else if(d == 1) {
        return "clrful-";//COLORFUL
    } else if(d == 2) {
        return "cyn-";//CYAN(scan Mode)
    } else if(d == 3) {
        return "wte-";//WHITE
    } else if(d == 4) {
        return "ylw-";//YELLOW
    } else if(d == 5) {
        return "red-";//RED
    } else if(d == 6) {
        return "blu-";//BLUE
    } else if(d == 7) {
        return "pnk-";//PINK
    }
    return "";
}
