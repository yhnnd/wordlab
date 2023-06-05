void Table::ShowAll(tablerow item[],int begin,int max,int Class,int x,int y, const int width) {

	int xOffset = 0;
#ifdef __APPLE__
	xOffset = 1;
#endif

	int r;
	this->Title(x, y, width, max);
	for (r = 1; r <= max; r++) {
        const int indentLeft = x + 4 + xOffset, indentTop = y + 2 + r;
	    gotoxy(indentLeft, indentTop);
        setColor(backlightwhite, "ShowAll");
		std::cout << std::right << std::setw(4) << r + begin << " ";
		std::cout << std::left;
        setColor(backdarkwhite, "ShowAll");
		if (item[r+begin].IsClass(Class)) {
			item[r+begin].printRow(indentLeft + 5, indentTop, width / tableRowConfigs.colMaxWidth - 2);
		}
	}
    setColor(lightwhite, "ShowAll");
}
