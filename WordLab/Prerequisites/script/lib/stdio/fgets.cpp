int scriptprocessor::scriptfgets(const char *line) {
	name = getname(line);
	value = getparam(line);
	if(value[0]=='\"') removebrackets(value,"\"","\"");
	FILE * fp = fopen(value.c_str(),"r");
	if(fp==NULL) {
		consolelogerror("fgets: fopen(%s) is null",value);
		return -1;
	} else {
		char s[64];
		fgets(s,64,fp);
		dataset.set(name,s);
	}
	fclose(fp);
	return 0;
}
