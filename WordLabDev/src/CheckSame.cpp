void checksame(){
	char **s;
	int i,j,lth,n,ln,lnprev,lnmax=Volume(lang::EN,1,30,"");
	progressbar Bar(2,1,1);
	for(lnprev=0,n=0,lth=1;lth<=30;lth++,lnprev+=ln){
		status("Check Same: checking library ",tostring(lth));
		if((ln=filelines(LibraryRoute(lth,EN),1))<=0) goto end;
		if((s=(char **)malloc(sizeof(char*)*ln))==NULL) goto end;
		for(int r=0;r<ln;r++) if((s[r]=(char *)malloc(sizeof(char)*32))==NULL) goto end;
		if(loadmsg(s,LibraryRoute(lth,EN),ln,32,1,0)<=0) goto end;
	    for(i=0;i<ln-1;i++){
	    	if(Bar.show(0,0,0,(lnprev+i)*ScreenX/lnmax,ScreenX)==-1) goto end;
	    	if(Bar.show(0,1,1,(i+1)*ScreenX/(ln-1),ScreenX)==-1) goto end;
	        for(j=i+1;j<ln;j++){
	            if(strcmp(s[i],s[j])==0){
					gotoxy(0,2+n++);
					cout<<s[i]<<"("<<i+1<<","<<j+1<<")";
				}
	        }
	    }
	}
	end:
	colorreset(white);
	if(n){
		gotoxy(0,2+n);
		cout<<"total: "<<n;
		getch();
	}else popup("no same words found");
}
