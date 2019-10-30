template <typename string>
int writefile(string msg,string filedir){
	int r;
	FILE *fp=fopen(filedir,"a");
	if(fp==NULL) return -1;
	else{
	    rewind(fp);
		for(r=0;msg[r][0]!=0;r++){
			fputs(msg[r],fp);
			fputc('\n',fp);
			}
		fclose(fp);
		}
	return 0;
}
