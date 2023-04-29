void window::alloc(){
	text._RowMax = filelines(title) + 32;
	text._ColMax = filelinesize(title) + 32;
	text._alloc();
}
void window::alloc(int PageSize,int LineSize){
	text._RowMax = PageSize;
	text._ColMax = LineSize;
	text._alloc();
}
