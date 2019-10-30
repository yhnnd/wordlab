int read(char *cmd_in,const char ***cmd,const char ***database){
	init();
	if((n_cmd=eval(cmd_in,cmd,4))==0) n_lib=eval(cmd_in,database,2);
	offset=queryProceed(n_cmd,n_lib,cmd_in);
	cmds[n++]=n_cmd;
	for(int i=0;cmd_in[i];i++){
		if(cmd_in[i]==' '&&cmd_in[i+1]!='\0'){
			if(offset==1){offset=0;continue;}
			if((n_cmd=eval(cmd_in+i+1,cmd,4))==0) n_lib=eval(cmd_in+i+1,database,2);
			offset=queryProceed(n_cmd,n_lib,cmd_in+i+1);
			cmds[n++]=n_cmd;
		}
	}
	cmds[n]=-1;
	return n;
}
