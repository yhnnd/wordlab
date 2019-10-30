int stroccurtimes(const char *str,const char *substr){
	int n,i,p,lth=strlen(substr);
	for(n=0,i=0;str[i]!='\0';){
		p = strindex(str+i,substr);
		if(p >= 0){
			n++;
			i+=p+lth;
		} else i++;
	}
	return n;
}
