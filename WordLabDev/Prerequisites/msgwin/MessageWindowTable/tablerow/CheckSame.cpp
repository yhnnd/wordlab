int tablerow::CheckSame(tablerow A,tablerow B,int colmax){
	int c;
	for(c=0;c<colmax;c++){
		if(strcmp(A.col[c],B.col[c])) break;
	}
	return c==colmax;
}
