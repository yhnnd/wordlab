int WoodPeckerCheckSyntax(int first,int last,int buffermax){
	int r,r1,error=0;
	char s[buffermax];
	FILE *fp;
	for(r=first;r<=last;r++){
	    if((fp=Library(r,CH,"r"))==NULL) return -1;
	    for(r1=1;!feof(fp);r1++){
		    fgets(s,buffermax,fp);
			if(WoodPeckerSyntaxError(s)){
			    error++;
			    if(error==1) cout<<"--- ---"<<endl<<"total  library  line   content"<<endl;
			    cout<<setw(4)<<error<<setw(7)<<r<<setw(8)<<r1<<"     "<<s<<endl;
			    if((error-10)%10==0){cout<<"press any key to continue."<<endl;getch();}
	        }
	    }
        fclose(fp);
    }
	if(error) cout<<"total unverified word "<<error<<endl;
	return error;
}
