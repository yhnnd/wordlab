int WoodPeckerCheckCongruence(int first,int last){
int r,r1,line1,line2,error=0;
char c,c1[last],c2[last];
FILE *fp1,*fp2;
for(r=first,line1=1;r<=last;r++){
	if((fp1=Library(r,EN,"r"))==NULL) return -1;
	if((fp2=Library(r,CH,"r"))==NULL) return -1;
	for(line2=1;;line1++,line2++){
		for(r1=0;(c=fgetc(fp1))!=EOF&&c!='\n'&&c!=' '&&c!='\0';) c1[r1++]=c;
		for(r1=0;(c=fgetc(fp2))!=EOF&&c!='\n'&&c!=' '&&c!='\0';) c2[r1++]=c;
        if(strncmp(c1,c2,r)){
		    error++;
		    if(error==1) cout<<"--- ---"<<endl<<"total library line english chinese"<<endl;
			cout<<line1<<"    "<<r<<"    "<<line2<<"    "<<c1<<"/"<<c2<<endl;
			}
		while((c=fgetc(fp2))!='\n') if(c==EOF) break;
		if(endfile(c1,c2,c)==1) break;
		}
	fclose(fp1);
	fclose(fp2);
	}
if(error) cout<<"total discordant word "<<error<<endl;
return error;
}
