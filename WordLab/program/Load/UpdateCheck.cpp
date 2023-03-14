void UpdateCheck(string msg){
	string lib = DatabaseVersion();
	string sys = SoftwareVersion();
	string lib_new,sys_new;
	int i=0,r=0,a=msg.find("("),b=msg.find(","),c=msg.find(")");
	if(a<0||b<0||c<0) goto NoUpdate;
	lib_new=string(msg,a+1,b-a-1);
	sys_new=string(msg,b+1,c-b-1);
	if(lib<lib_new&&sys<sys_new){
		Update:
		string version= string("database:")+lib_new+" system:"+sys_new;
		popup("<-wte>(a new version <-grn>(",version,")<-wte>( is available)",0);
	}else{
		NoUpdate:
		string version = string("database:")+lib+" system:"+sys;
		popup("<-wte>(current version <-ylw>(",version,")<-wte>( is up to date)",0);
	}
}

