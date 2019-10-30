int maths::filter(int n,int *flag,int *i){
	int r;
	for(r=0;r<*i;r++) if(flag[r]==n) return r;
	flag[r++]=n;
	*i=r;
	return 0;
}
