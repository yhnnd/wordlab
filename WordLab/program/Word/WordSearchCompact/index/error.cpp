bool indexerror(){
	bool flag = false;
	FILE *fp1=fopen(EnglishRoute,"r"),*fp2=fopen(ChineseRoute,"r");
	if(fp1==NULL||fp2==NULL){
		cout<<"Index Engine: Data Lost";
		flag = true;
	}
	fclose(fp1);
	fclose(fp2);
	return flag;
}
