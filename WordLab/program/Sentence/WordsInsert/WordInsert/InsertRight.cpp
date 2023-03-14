void Word_Right_Insert(int a,int b) {
	int r,lth=b-a;
	char scopy[31];
	strcpy(scopy,s[a].txt);
	for(r=0; r<=lth-1; r++) strcpy(s[a+r].txt,s[a+r+1].txt);
	strcpy(s[b].txt,scopy);
	return;
}
