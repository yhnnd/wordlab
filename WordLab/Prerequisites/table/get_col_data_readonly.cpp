const bool _table::getReadOnly(int r,int c){
	return toInt(getTagElement(r,c,3))%10;
}
