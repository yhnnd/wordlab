void Table::ShowAll(tablerow item[],int begin,int max,int Class,int x,int y,int width) {

	int xOffset = 0;
#ifdef __APPLE__
	xOffset = 1;
#endif

	int r;
	this->Title(x,y,width,max);
	for (r = 1; r <= max; r++) {
	    gotoxy(x + 4 + xOffset, y + 2 + r);
		colorset(backlightwhite);
		std::cout << std::right << std::setw(4) << r + begin << " ";
		std::cout << std::left;
		colorset(backdarkwhite);
		if (item[r+begin].IsClass(Class)) {
			item[r+begin].Out();
		}
	}
	colorset(lightwhite);
}
