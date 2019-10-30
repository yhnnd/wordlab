const bool _table::getReadOnly(int r,int c){
	return toint(getTagElement(r,c,3))%10;
}
