int scriptprocessor::scriptgetch(const char *line){
	name = getname(line);
	if(_debug) {
		colorrecord(ogcolor);
		colorset(light|green|backcyan);
		printf(" getch ");
		colorreset(ogcolor);
	}

    const char ch = getch();
    value = ch;
	if (value == "\r") {
        value = "\\r";
    }
	dataset.set(name,value);
	return 0;
}
