int delayof(int n,int max){
	static int div=1;
	for(;;){
		if(n/div<max) return n/div;
		else div++;
	}
}
