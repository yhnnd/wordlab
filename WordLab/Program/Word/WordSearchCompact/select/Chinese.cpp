int SelectChineseShow(const char word_a[],const char word_b[],FILE *fp){
	char c;
	if(strcmp(word_a,word_b)==0){
		for(;(c=fgetc(fp))!='\n';) if(c!=' ') cout<<c;
		return 1;
	}
	return -1;
}

int SelectChineseCore(const char keyword[],FILE *fp){
	char loadword[30],c;
	int r,t;
	for(r=0;(c=fgetc(fp))!=EOF;){
	    if(c==' '){
	        for(t=r;t<=strlen(loadword);t++) loadword[t]='\0';
	        if(SelectChineseShow(keyword,loadword,fp)==1){
				fclose(fp);
				return 1;
			}
	    }else if(c=='\n') r=0;
	    else if(isalpha(c)) loadword[r++]=c;
	    }
	fclose(fp);
	return 0;
}

int SelectChinese(const char keyword[]){
	FILE * fp=fopen(ChineseRoute,"r");
	if(SelectChineseCore(keyword,fp)==1){
		fclose(fp);
		return 1;
	}
	fclose(fp);
	return 0;
}
