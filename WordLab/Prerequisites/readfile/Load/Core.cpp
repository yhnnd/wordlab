int loadmsg(char *msg,FILE *fp,int maxlines,int linemax,bool close,bool modify){
	int n=0;
	do{
		char *p=msg+n*linemax;
		fgets(p,linemax,fp);
		for(int i=strlen(p)-1;i>=0;i--){//delete \n,EOF,; at the end of string
			if(*(p+i)=='\n'||*(p+i)==EOF||(modify&&*(p+i)==';')) *(p+i)=0;
			else break;
		}
		n++;
	}while(n<maxlines&&!feof(fp));
	if(n<maxlines) memset(msg+n*linemax,0,sizeof(char)*linemax);
	if(close) fclose(fp);
	return n;
}
int loadmsg(char **msg,FILE *fp,int maxlines,int linemax,bool close,bool modify){
	int n=0;
	do{
		fgets(msg[n],linemax,fp);
		for(int i=strlen(msg[n])-1;i>=0;i--){//delete \n,EOF,; at the end of string
			if(msg[n][i]=='\n'||msg[n][i]==EOF||(modify&&msg[n][i]==';')) msg[n][i]=0;
			else break;
		}
		n++;
	}while(n<maxlines&&!feof(fp));
	if(n<maxlines) memset(msg[n],0,sizeof(char)*linemax);
	if(close) fclose(fp);
	return n;
}
