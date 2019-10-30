int findStrict(const char *msg,const char *filename){
int line,n,r;
char c,msgfile[100];
FILE*fp=fopen(filename,"r");
if(fp==NULL){
	errorlog("findstrict","cannot open ",filename);
	return -1;
	}
for(line=1,n=0,r=0,rewind(fp),strclr(msgfile);;){
    c=fgetc(fp);
	if(c=='\n'||c==EOF){
	    if(strcmp(msg,msgfile)==0) n++;
	    line++;r=0;strclr(msgfile);
		}
	else msgfile[r++]=c;
	if(c==EOF) break;
    }
fclose(fp);
return n;
}
