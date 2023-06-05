int scriptprocessor::scriptGetch(const char *line){
	name = getname(line);
	if(_debug) {
		recordColor(ogcolor, "scriptGetch");
        setColor(lightgreen | backcyan, "scriptGetch");
		printf(" getch ");
		resetColor(ogcolor, "scriptGetch");
	}

    const char ch = getch();
    value = ch;
	if (value == "\r") {
        value = "\\r";
    }
	dataset.set(name,value);
	return 0;
}
