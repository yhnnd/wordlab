int MessageWindowLoad(tablerow *item,const char *filename){
	int r,maxwidth=1024;
	char msg[maxwidth];
	FILE *fp=fopen(filename,"r");
	if(fp==NULL) return 0;
	for(r=1;fgets(msg,maxwidth,fp);){
		item[r].colmaxwidth=128;
		r=item[r].Load(r,msg);
	}
	fclose(fp);
	return r-1;
}
