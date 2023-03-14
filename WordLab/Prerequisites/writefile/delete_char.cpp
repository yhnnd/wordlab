int DeleteChar(const char *route,const int n){
	char ch,s[200];
	int r,NOL=1;
	FILE *fp=fopen(route,"r");
	FILE *fbuf=fopen("buf.txt","w");
	if(fp==NULL) return -1;
	while((ch=fgetc(fp))!=EOF){
		if(ch=='\n') NOL++;
		if(NOL!=n) fputc(ch,fbuf);
		else break;
		}
	for(r=0;(ch=fgetc(fp))!=false;r++){s[r]=ch;if(ch=='\n'||ch==EOF)break;}
	strclr(s,r-1);
	if(s[0]) fputc('\n',fbuf);
	fputs(s,fbuf);
	fclose(fp);
	fclose(fbuf);
	remove(route);
	rename("buf.txt",route);
	if(NOL<n) return 1;
	return 0;
}
