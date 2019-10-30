void printColorful(const char *msg){
	int r;
	for(r=0;msg[r]!=0;r++){
		Colorful(r);
		std::cout<<msg[r];
	}
}
