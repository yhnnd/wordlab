int maths::operatorright(PKC s,int br,PKC operators,PKC br1,PKC br2){
	int i=0;
	for(i=0;s[i]!=0;i++){
    	if(strchr(br1,s[i])!=NULL) {
            ++br;
        }
    	if(strchr(br2,s[i])!=NULL) {
            --br;
        }
    	if(br==0&&strchr(operators,s[i])) {
            break;
        }
    }
	return (s[i]!='\0')?i:0;
}
