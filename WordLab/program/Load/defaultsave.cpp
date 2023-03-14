int defaultsave(const char * route,int i,...){
    va_list argv;
    va_start(argv,i);
	char *typemsg;
	ofstream fout(route,ios::out);
    while(i--){
    	typemsg=va_arg(argv,char *);//type
		fout<<va_arg(argv,char *);//msg
		fout<<va_arg(argv,int);//value
		fout<<endl;
		//'bool' is promoted to 'int' when passed through '...'
		//'char' is promoted to 'int' when passed through '...'
    	}
    fout.close();
    va_end(argv);
    return 0;
}
