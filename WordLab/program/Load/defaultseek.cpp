char load::defaultseek(char *msgs,int m,int n,char *msg) {
    int r;
    for(r=0;r<m;r++) if(strindex(msgs+n*r,msg)==0) break;
	if(strlen(msgs+n*r)<strlen(msg)+1) return 0;
    return *(msgs+n*r+strlen(msg))-'0';
}
