int sortlib(int bgn,int end,const string admin,const string pwd) {
	int i,ln;
	char **s_en,**s_ch;
	if (bgn > end) return sortLibError(-8);
	for(i=bgn; i<=end; i++) {
		//validate
		if(!LibraryAdminValidate(i,EN,admin,pwd)) return sortLibError(-7,admin);
		//read
		if((ln=filelines(LibraryRoute(i,EN),1))<=0) return sortLibError(-1);
		if((s_en=(char **)malloc(sizeof(char*)*ln))==NULL) return sortLibError(-2);
		for(int r=0; r<ln; r++) if((s_en[r]=(char *)malloc(sizeof(char)*32))==NULL) return sortLibError(-2);
		if((s_ch=(char **)malloc(sizeof(char*)*ln))==NULL) return sortLibError(-2);
		for(int r=0; r<ln; r++) if((s_ch[r]=(char *)malloc(sizeof(char)*256))==NULL) return sortLibError(-2);
		if(loadmsg(s_en,LibraryRoute(i,EN),ln,32,1,0)<=0) return sortLibError(-3);
		if(loadmsg(s_ch,LibraryRoute(i,CH),ln,256,1,0)<=0) return sortLibError(-3);
		//sort
		for(int r=0; r<ln-1; r++) {
			for(int j=r+1; j<ln; j++) {
				if(strcmpi(s_en[r],s_en[j])>0) {
					strswap(s_en[r],s_en[j],32);
					strswap(s_ch[r],s_ch[j],256);
				}
			}
		}
		//record
		FILE *fp_en,*fp_ch;
		if((fp_en=fopen("lib_en.dat","w"))==NULL) return sortLibError(-5);
		if((fp_ch=fopen("lib_ch.dat","w"))==NULL) return sortLibError(-5);
		for(int r=0; r<ln; r++) {
			if(strncmp(s_en[r],s_ch[r],i)) {
				sortLibError(-4,s_en[r]);
				continue;
			}
			fputs(s_en[r],fp_en);
			fputs(s_ch[r],fp_ch);
			if(r==ln-1) break;
			fputc('\n',fp_en);
			fputc('\n',fp_ch);
		}
		fclose(fp_en);
		fclose(fp_ch);
		//rewrite
		remove(LibraryRoute(i,EN).c_str());
		if(rename("lib_en.dat",LibraryRoute(i,EN).c_str())!=0) return sortLibError(-6);
		remove(LibraryRoute(i,CH).c_str());
		if(rename("lib_ch.dat",LibraryRoute(i,CH).c_str())!=0) return sortLibError(-6);
		//free memory
		for(int r=0; r<ln; r++) {
			free(s_en[r]);
			free(s_ch[r]);
		}
		free(s_en);
		free(s_ch);
	}
	string message="from <ylw->(lth="+tostring(bgn)+") to <ylw->(lth="+tostring(end)+")";
	return sortLibError(0,message);
}
