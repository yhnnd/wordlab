void history::read(const char *route,const char *title){
	FILE * fp=NULL;
	if((fp=fopen(route,"r"))==NULL) popup("<ylw->(",title,") HAS BEEN DELETED;",0);
	else Table.table(route);
	fclose(fp);
}
