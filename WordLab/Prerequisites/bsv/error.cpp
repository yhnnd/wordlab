int bsverror(const char *s1,const char *s2,const char *s3){
	char msg[strlen(s1)+strlen(s2)+strlen(s3)-2];
	strcpy(msg,s1);
	strcat(msg,s2);
	strcat(msg,s3);
	recordxy(xy);
	gotoxy(0,0);
	bsvline(msg,ScreenX-1);
	resetxy(xy);
	wait(-1,100,0);
    return 0;
}
