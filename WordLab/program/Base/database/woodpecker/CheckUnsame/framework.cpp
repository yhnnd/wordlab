int WoodPeckerCheckCongruence(int first,int last){
    int r,r1,line1,line2,error=0;
    char c,c1[last],c2[last];
    FILE *fp1,*fp2;
    for(r=first,line1=1;r<=last;r++) {
        if((fp1=Library(r,EN,"r"))==NULL) return -1;
        if((fp2=Library(r,CH,"r"))==NULL) return -1;
        for(line2=1;;line1++,line2++) {
            memset(c1, 0, sizeof(c1));
            memset(c2, 0, sizeof(c2));
            for (r1=0; (c=fgetc(fp1))!=EOF && c!='\n' && c!=' ' && c!='\0';) {
                if (isprint(c)) {
                    c1[r1++] = c;
                } else {
                    c1[r1++] = '?';
                }
            }
            for (r1=0; (c=fgetc(fp2))!=EOF && c!='\n' && c!=' ' && c!='\0';) {
                if (isprint(c)) {
                    c2[r1++] = c;
                } else {
                    c2[r1++] = '?';
                }
            }
            if(strncmp(c1,c2,r)) {
                error++;
                if (error==1) {
                    cout<<"--- ---"<<endl;
                    printf("%10s %10s %10s %30s %s\n", "total", "library", "line", "english", "chinese");
                }
                printf("%10d %10d %10d %30s %s\n", line1, r, line2, c1, c2);
            }
            while ((c=fgetc(fp2))!='\n') {
                if(c==EOF) break;
            }
            if(endfile(c1,c2,c)==1) {
                break;
            }
        }
        fclose(fp1);
        fclose(fp2);
    }
    if (error) {
        cout<<"total discordant word "<<error<<endl;
    }
    return error;
}
