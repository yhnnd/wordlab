int scriptprocessor::scriptGets(const char *line){
	name = getparam(line);
	if(_debug){
		recordColor(ogcolor, "scriptGets");
        setColor(lightgreen | backcyan, "scriptGets");
		printf(" input ");
		resetColor(ogcolor, "scriptGets");
	}
	std::cin >> value;
	dataset.set(name,value);
	return 0;
}
