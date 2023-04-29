bool load::defaults(const char *route,bool in) {
	FILE *fp=fopen(route,"rb");
	if(fp==NULL){popup("<red->(config error) default file not found",-1);return false;}
	fclose(fp);
	int max=17,n=filelines(route,true);
	if(in){
		char s[n][LINEMAX];
    	if(loadmsg((char*)s,route,n,LINEMAX,1,1)<=0){
			popup("<red->(config error) default file is empty",-1);
			return false;
		}
    	defaultload(&s[0][0],n,LINEMAX,max,
			"bool","Ask=",&_Ask,"bool","Show=",&_Show,"bool","Color=",&ColorL,
			"bool","Language=",&LANGUAGE,"bool","SayStyle=",&SayStyle,"bool","Version=",&version,
			"int","Color[0]=",&CLRL[0],"int","Color[1]=",&CLRL[1],"bool","Ctype=",&Ctype,
			"bool","VL=",&VL,"bool","AL=",&AL,"bool","BL=",&BL,"bool","CL=",&CL,"bool","DL=",&DL,
			"bool","SL=",&SL,"bool","IL=",&IL,"bool","ML=",&ML);
    }else defaultsave(route,max,
		"bool","Ask=",_Ask,"bool","Show=",_Show,"bool","Color=",ColorL,
		"bool","Language=",LANGUAGE,"bool","SayStyle=",SayStyle,"bool","Version=",version,
		"int","Color[0]=",CLRL[0],"int","Color[1]=",CLRL[1],"bool","Ctype=",Ctype,
		"bool","VL=",VL,"bool","AL=",AL,"bool","BL=",BL,"bool","CL=",CL,"bool","DL=",DL,
		"bool","SL=",SL,"bool","IL=",IL,"bool","ML=",ML);
	return true;
}
