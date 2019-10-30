int dialog::outputfile(const char *filename,int n,WORD color) {
	FILE*fp=fopen(filename,"r");
	if(fp==NULL) {
		status("sayfile: cannot open ",filename);
		return -1;
	} else status("sayfile: loading ",filename);
	char msg[LINEMAX];
	int r,max=filelines(fp,false);
	rewind(fp);
	roll(n,n,0,max-1);
	for( r = 0; r <= n; r++ ) fgets(msg,LINEMAX,fp);
	output(msg,color);
	fclose(fp);
	return n;
}
