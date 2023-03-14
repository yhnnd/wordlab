int WLSearchFuzzy(const char *s,int Limit){
	char key,c[30];
	int r,ch,k,km,n=0,NOL=1,lth=strlen(s);
	FILE *fp=Library(lth,EN,"r");
	while(EOF!=(ch=getc(fp))) if(ch=='\n')++NOL;
	for(k=1;k<=NOL;k++){
	    fseek(fp,(k-1)*(lth+2),0);
	    fread(&c,lth,1,fp);
	    rewind(fp);
	    strclr(c,lth);
	    for(km=0,r=0;r<lth;r++) if(s[r]==c[r]) km=km+1;
	    if(km==lth) goto CORRECT;
	    if(km>=lth-Limit){
	    	key=WLSearchFuzzyAsk(popup(" Do you mean ",c," ?",3000));
	        if(key==1){
	        	CORRECT:
				WLSearchCore(lth,NOL,c,k);
				n++;
				break;
			}
	        else if(key==-1) break;
	    }
	}
	fclose(fp);
	return n;
}
