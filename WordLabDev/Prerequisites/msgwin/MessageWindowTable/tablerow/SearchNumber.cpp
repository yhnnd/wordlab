int tablerow::SearchNumber(const char *number){
	if(strcmp(col[2],number)==0){
		std::cout<<col[1]<<" "<<col[2]<<std::endl;
		return 1;
	}
	return 0;
}
