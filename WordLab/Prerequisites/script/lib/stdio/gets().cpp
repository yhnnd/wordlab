int scriptprocessor::scriptGetsVoid(const char *line) {
	name = getname(line);
	if(_debug) {
		recordColor(ogcolor, "scriptGetsVoid");
        setColor(lightgreen | backcyan, "scriptGetsVoid");
		printf(" input ");
		resetColor(ogcolor, "scriptGetsVoid");
	}
	std::cin>>value;
	dataset.set(name,value);
	return 0;
}
