int eval(char *cmd_in,const char ***cmd,int max){
	int l,i;
	for(l=0;cmd_in[l]&&cmd_in[l]!=' ';l++);
	char cmd_in_trim[l+1];
	for(i=0;i<l;i++) cmd_in_trim[i]=cmd_in[i];
	cmd_in_trim[i]='\0';
	
	for(l=0;l<max;l++){
		for(i=0;cmd[l][i][0]!='#';i++){
			if(strcmp(cmd_in_trim,cmd[l][i])==0){
				return (l+1)*100+i;
			}
		}
	}
	if(max==2&&l==max&&cmd[l-1][i][0]=='#') evalbr(cmd_in_trim);
	return 0;
}

