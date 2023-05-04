void togglesShow(int x,int y,int width,bool showdigit,int n,...){
	int r;
    va_list argv;
    va_start(argv,n);
	for (r = 1; r <= n; r++) {
        toggleShow(x+width-1,y+1+r,va_arg(argv,int),false,showdigit);
    }
    va_end(argv);
}
