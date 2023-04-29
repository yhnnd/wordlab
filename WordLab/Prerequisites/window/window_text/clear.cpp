int window::text::clear(){
	if(ptr==nullptr) return setsize(0)==0;
	for(int i=0;i<sizeof(ptr);i++) free(ptr[i]);
	free(ptr);
	ptr = nullptr;
	free(iscmd);
	iscmd = nullptr;
	return setsize(0)==0;
}
