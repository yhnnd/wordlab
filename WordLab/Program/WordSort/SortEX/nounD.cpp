int SortEX_DefinitelyNOUN(char s[]) { //���ʼ���(С)
	if(
	    WordSort(s)==1||//n.
	    WordSort(s)==3||//adj.
	    WordSort(s)==11//art.
	)return 0;
	return -1;
}
