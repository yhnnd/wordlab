void Word_Left_Insert(int a,int b) {
	int r,lth=b-a;
	char scopy[31];
	strcpy(scopy,s[b].txt);
	for(r=lth-1; r>=0; r--) strcpy(s[a+r+1].txt,s[a+r].txt);
	strcpy(s[a].txt,scopy);
	return;
}
