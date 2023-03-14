void filein(char msg[][LINEMAX],const char *route) {
	int r=0,r1=0;
	char c=0;
	FILE *fp=fopen(route,"r");
	rewind(fp);
	while(true) {
		c=fgetc(fp);
		if(c==';') {
			while(true) {
				c=fgetc(fp);
				if(c=='\n'||c==EOF) break;
			}
		}
		if(c==EOF) {
			strclr(msg[r],r1);
			break;
		}
		if(c=='\n') {
			strclr(msg[r],r1);
			r++;
			r1=0;
		} else msg[r][r1++]=c;
	}
	fclose(fp);
}
