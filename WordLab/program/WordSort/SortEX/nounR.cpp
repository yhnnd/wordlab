int SortEX_REALNOUN(char s[]) { //���ʼ���(��)
	if(
	    (WordSort(s)==1||//n.
	     WordSort(s)==8||//pron.
	     WordSort(s)==3||//adj.
	     WordSort(s)==11//art.
	    ) && SortEX_WH(s)!=0
	)
		return 0;
	return -1;
}
