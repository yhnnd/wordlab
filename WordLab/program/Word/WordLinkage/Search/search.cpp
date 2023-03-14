int WLSearch(string s,bool ignoreCase){
	int lth = s.length();
	FILE *fp = Library(lth,EN,"r");
	char c[32];
	int k=0,kprev[36],kn=0,a=0,z=0,number=0,n=filelines(fp,0),flag=0;
	for(a=1,z=n;(a<z&&(a==1||z==n))||(a<z-1&&a>1&&z<n);){
		k=a+(flag>0?ceil((z-a)/2.0):floor((z-a)/2.0));
		if(maths::filter(k,kprev,&kn)) break;
	    fseek(fp,(k-1)*(lth+2),0);
		fread(&c,lth,1,fp);
		rewind(fp);
		if( ignoreCase ) flag = strnicmp(s.c_str(),c,lth);
		else flag = strncmp(s.c_str(),c,lth);//Xprmt'l updated 2017.03.14
	    if( flag<0 ) z=k;
		else if(flag>0) a=k;
		else{
			WLSearchCore(lth,n,c,k);
			number++;
			break;
		}
	}
	fclose(fp);
	if(number==0){
	    WLHistory.RecordAnswer(s.substr(0,lth),0);
		WLHistory.RecordUnfound(s.substr(0,lth),0);
	}
	return number;
}
