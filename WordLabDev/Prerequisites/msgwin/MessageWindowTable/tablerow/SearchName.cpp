int tablerow::SearchName(const char * name){
	if(strcmp(col[1],name)==0){
		std::cout<<col[1]<<" "<<col[2]<<std::endl;
		return 1;
	}
	return 0;
}
