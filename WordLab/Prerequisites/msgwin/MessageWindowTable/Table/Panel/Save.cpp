int Save(tablerow item[],const char *filename,int Total){
	FILE *fp=fopen(filename,"w");
	if(fp==NULL) return -1;
	for(int r=1;r<=Total;r++) item[r].Save(r,fp);
	fclose(fp);
	return 0;
}
