void dialog::outputrand(const char *filename,WORD color) {
	FILE*fp=fopen(filename,"r");
	if(fp==NULL) {
		status("randsay: cannot open ",filename);
		return;
	} else status("randsay: loading ",filename);
	char msg[LINEMAX];
	int r,n,max=filelines(fp,0);
	n=rand()%max;
	rewind(fp);
	for(r=0; r<=n; r++) fgets(msg,LINEMAX,fp);
	output(msg);
	fclose(fp);
}
