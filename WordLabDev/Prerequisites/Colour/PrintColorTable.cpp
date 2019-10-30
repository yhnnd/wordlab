void printcolortable(){
//	setscreen(120,30);
	colorset(white);
	char cmd[8][4]={"lit","blu","grn","cyn","red","ppl","ylw","wte"};
	std::cout<<std::setw(6)<<"";
	for(int i=0;i<16;++i){
		std::cout<<" "<<(i<8?"#":" ")<<cmd[i%8]<<"-";
	}
	std::cout<<std::endl;
	for(int i=0;i<256;++i){
		colorset(backwhite);
		if(i%16==0) std::cout<<(i/16<8?"-#":" -")<<cmd[i/16%8]<<" ";
		colorset(i);
		std::cout<<std::setw(6)<<i;
		if(i%16==15) std::cout<<std::endl;
	}
}
