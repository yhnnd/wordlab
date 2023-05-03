int WLSearchPhrase(const char *msg){
	int r=0,n=1,l=0;
	char s[64],line[64];
	strcpy(s,",");
	strcat(s,msg);
	for(r=0;s[r]!=0;r++){
		if(s[r]==' '){
			n++;
			s[r]=',';
		}
	}
	s[r++]=',';
	s[r]=0;
	char route[64]=PhraseRouteA;
	strcat(route,toString(n).c_str());
	strcat(route,PhraseRouteB);
	FILE *fp = fopen(route,"r");
	do{
		l++;
		fgets(line,64,fp);
		if(strstr(line,s)==line){
			cout<<n<<"/"<<l<<" "<<line;
			return l;
		}
	}while(!feof(fp));
	fclose(fp);
	return 0;
}
