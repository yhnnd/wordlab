int legal(char c,bool csv=1){
	if(c=='\n'||c=='\0'||c==EOF) return -1;
    if(isspace(c)||iscntrl(c)||(csv&&c==',')) return 0;
	return 1;
}

int tablerow::Load(int Total,char *msg) {
    int r=0,r1,colmax=4;
	order=Total;
	for(int c=0;c<colmax&&legal(msg[r])!=-1;c++){
		for(r1=0;r1<colmaxwidth-1&&legal(msg[r])>0;r++,r1++) col[c][r1]=msg[r];
		strclr(col[c],r1);
		if(legal(msg[r])!=-1) {
            for(;legal(msg[r])==0;r++);
        }
	}
	return Total+1;
}
