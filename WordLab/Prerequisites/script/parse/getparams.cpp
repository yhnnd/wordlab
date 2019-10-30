int scriptprocessor::getparams(char **params,const char *line,int max,const char *begintoken,const char *endtoken){
	int i=strindex(line,"(")+1,j=0,l=strlen(line);
	for(j=0;j<max&&i<l;j++){
		i+=getparamsparse(params[j],line+i,endtoken)+1;
	}
	return j - max;
}
