int filelines(FILE *fp,bool close,bool debug){
	int NOL=1;
	char ch;
	if(fp==NULL){
		if(debug) errorlog("FileLines","error opening file");
		return EOF;
		}
	else while(EOF!=(ch=getc(fp))) if(ch=='\n') ++NOL;
	if(close) fclose(fp);
	else rewind(fp);
	return NOL;
}

int filelines(const std::string route,bool debug){
	FILE *fp=fopen(route.c_str(),"r");
	if(fp==NULL){
		if(debug) errorlog("FileLines","cannot open ",route);
		return EOF;
		}
	else return filelines(fp,1,debug);
}
