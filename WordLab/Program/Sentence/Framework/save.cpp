void save(bool out=true) {
	int r;
	static word v[MAXIMUM];
	if(out) for(r=0; r<=rwin; r++) strcpy(v[r].txt,s[r].txt);
	else    for(r=0; r<=rwin; r++) strcpy(s[r].txt,v[r].txt);
}
