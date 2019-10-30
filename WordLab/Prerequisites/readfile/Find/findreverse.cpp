int findreverse(const char *msg,FILE *fp,bool close){
	int line,n,r;
	char c,msgfile[100];
	if(fp==NULL){
		errorlog("Find Reverse","error open file");
		return 0;
		}
	for(line=1,n=0,r=0;(c=fgetc(fp))!=EOF;){
		if(c=='\n'){
		    if(strindex(msgfile,msg)!=-1) n++;
		    line++;r=0;strclr(msgfile);
			}
		else msgfile[r++]=c;
	    }
	if(close) fclose(fp);
	return n;
}

int findreverse(const char *msg,const char *route){
	int n=0;
	FILE *fpr=fopen(route,"r");
	if(fpr==NULL) errorlog("Find Reverse","error open ",route);
	else n=findreverse(msg,fpr,1);
	return n;
}
