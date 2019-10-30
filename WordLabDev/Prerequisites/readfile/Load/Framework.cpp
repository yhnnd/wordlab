int loadmsg(char* msg,std::string route,int maxlines,int linemax,bool close,bool modify){//modify=1
	FILE *fp=fopen(route.c_str(),"r");
	if(fp==NULL){
		errorlog("loadmsg","cannot open ",route);
		return 0;
	}
	return loadmsg(msg,fp,maxlines,linemax,1,modify);
}

int loadmsg(char** msg,std::string route,int maxlines,int linemax,bool close,bool modify){//modify=1
	FILE *fp=fopen(route.c_str(),"r");
	if(fp==NULL){
		errorlog("loadmsg","cannot open ",route);
		return 0;
	}
	return loadmsg(msg,fp,maxlines,linemax,1,modify);
}

