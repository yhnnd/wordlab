int getChineseOfWord(char *s,bool Show=true) {
	char c[30];
	int r,k,km,number=0,lth=strlen(s);
	FILE *fp = Library(lth,EN,"r");
	int NOL=filelines(fp,false);
	for(k=1; k<=NOL; k++) {
		fseek(fp,(k-1)*(lth+2),0);
		fread(&c,lth,1,fp);
		rewind(fp);
		for(km=0,r=0; r<lth; r++) if(s[r]==c[r]) km=km+1;
		if(km==lth) {
			if(Show) {
				colorset(light|green);
				cout<<Translation(lth,k);
			}
			number=1;
			break;
		}
	}
	fclose(fp);
	return number;
}

int getChineseOfWord_S(char *s,bool Show=true,int Limit=1) {
	char c[30];
	int r,k,km,number=0,lth=strlen(s);
	FILE *fp=Library(lth,EN,"r");
	int NOL=filelines(fp,false);
	for(k=1; k<=NOL; k++) {
		fseek(fp,(k-1)*(lth+2),0);
		fread(&c,lth,1,fp);
		rewind(fp);
		for(km=0,r=0; r<lth; r++) if(s[r]==c[r]) km=km+1;
		if(km>=lth-Limit) {
			if(Show) {
				colorset(light|yellow);
				cout<<Translation(lth,k);
			}
			number++;
			break;
		}
	}
	fclose(fp);
	return number;
}
