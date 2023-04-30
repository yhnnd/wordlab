void init(){
	n=0;
	n_cmd=0;
	n_lib=0;
	offset=0;
	attr_n=0;
	attr_max=6;
	for(int i=0;i<attr_max;i++) attr[i].clear();
	orderby.clear();
	groupby.clear();
	memset(cmds,0,sizeof(cmds));
}
