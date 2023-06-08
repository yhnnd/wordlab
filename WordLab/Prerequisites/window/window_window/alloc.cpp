void window::alloc(){
	text._RowMax = fileLines(title) + 32;
	text._ColMax = fileLineSize(title) + 32;
	text._alloc();
}
void window::alloc(int PageSize,int LineSize){
	text._RowMax = PageSize;
	text._ColMax = LineSize;
	text._alloc();
}
