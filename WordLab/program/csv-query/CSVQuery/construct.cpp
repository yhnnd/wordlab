csvquery(){}
csvquery(char *cmd_in){
	const char *cmd_funct[]={"cmd_funct:","select","create","delete","insert","update","fetch",
	"drop","add","open","set","alter","order_by","group_by","print","system","join","check","#"};
	const char *cmd_scope[]={"cmd_scope:","where","from","to","in","between","of","#"};
	const char *cmd_conj []={"cmd_conj:","and","or","not","if","else","#"};
	const char *cmd_data []={"cmd_data:","library","source","#"};
	const char **cmd[]={cmd_funct,cmd_scope,cmd_conj,cmd_data};
	const char *data_name[]={"database_name:","word:en","word:en-ch","phrase:en-ch","#"};
	const char *data_type[]={"database_type:","global","skyside","#"};
	const char **database[]={data_name,data_type};
	read(cmd_in,cmd,database);
}
