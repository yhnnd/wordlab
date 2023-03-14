int scriptprocessor::scriptgetch(const char *line){
	name = getname(line);
	if(_debug){
		colorrecord(ogcolor);
		colorset(light|green|backcyan);
		printf(" getch ");
		colorreset(ogcolor);
	}
	value[0] = wl_getch();
	value[1] = 0;
	if(value[0]=='\r') value = "\\r";
	dataset.set(name,value);
	return 0;
}
