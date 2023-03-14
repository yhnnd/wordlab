int defaultload(char *msgs,int m,int n,int i,...){
    va_list argv;
    va_start(argv,i);
	char *typemsg=NULL,type;
    bool *pbool=NULL;
    char *pchar=NULL;
    int v,*pint=NULL;
    while(i--){
    	typemsg=va_arg(argv,char *);
		v=defaultseek(msgs,m,n,va_arg(argv,char *));
    	type=(strcmp(typemsg,"bool")==0)?2:
			(strcmp(typemsg,"char")==0)?8:
			(strcmp(typemsg,"int")==0||strcmp(typemsg,"long")==0)?32:0;
		switch(type){
			case 2: *va_arg(argv,bool *)=v; break;
			case 8: *va_arg(argv,char *)=v; break;
			case 32: *va_arg(argv,int *)=v; break;
			default: va_arg(argv,void *); break;
			}
    	}
    va_end(argv);
}
