int scriptprocessor::scriptfputs(const char *line){// fputs(str,route,mode)
	char param[3][32];// param 1 string, param 2 route, param 3 mode
	std::string mode;
	memset(param,0,sizeof(param));
	char *paramptr[3] = {param[0],param[1],param[2]};
	FILE *fp = NULL;
	getparams(paramptr,line,3);// get params
	// fetch route
	value = param[1];
	if(param[1][0]=='\"') removebrackets(value,"\"","\"");
	else value = dataset.getvalue(param[1]);
	// fetch mode
	mode = param[2];
	if(param[2][0]=='\"') removebrackets(mode,"\"","\"");
	else mode = dataset.getvalue(param[2]);
	// open file
	if((fp=fopen(value.c_str(),mode.c_str()))==NULL){
		consolelogerror("cannot open file(%s,%s)",value,mode);
		return 0;
	}
	// fetch string
	if(param[0][0]=='\"') value = param[0];
	else value = dataset.getvalue(param[0]);
	removebrackets(value,"\"","\"");
	fputs(value.c_str(),fp);
	fclose(fp);
	return 0;
}
