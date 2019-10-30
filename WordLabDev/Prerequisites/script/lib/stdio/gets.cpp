int scriptprocessor::scriptgets(const char *line){
	name = getparam(line);
	if(_debug){
		colorrecord(ogcolor);
		colorset(light|green|backcyan);
		printf(" input ");
		colorreset(ogcolor);
	}
	std::cin>>value;
	dataset.set(name,value);
	return 0;
}
