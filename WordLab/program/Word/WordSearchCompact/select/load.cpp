int SelectLoad(char wordbase[],FILE *fp){
	int t = 0;
	char c;
	while(true){
		c=fgetc(fp);
		if(c==EOF) return -1;
		else if(isalpha(c)==0){
			wordbase[t]='\0';
			break;
		}else wordbase[t++]=c;
	}
	return 0;
}
