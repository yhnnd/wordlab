char* strclr(char *s,int i){
	if(i<0) return s;
    for(;s[i]!='\0';i++) s[i]='\0';
    return s;
}
