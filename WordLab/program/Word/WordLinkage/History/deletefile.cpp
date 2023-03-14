template <typename str>
void history::deletef(str route,str title){
	FILE *fp=NULL;
	if((fp=fopen(route,"r"))==NULL){
		popup("<fore yellow>(",title,") already deleted;",0);
		return;
	}
	fclose(fp);
	remove(route);
	if((fp=fopen(route,"r"))==NULL) popup("<fore yellow>(",title,") deleted;",0);
	else popup("unable to delete <fore yellow>(",title,");",-1);
	fclose(fp);
}
