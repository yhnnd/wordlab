int findinfolder(PKC handle,PKC folderpath){
	int r = 0, n = 0;
	char c = 0, FileDirTemp[100], dir[100], bufroute[]="buf.dat";
	FILE *fp = fopen(bufroute,"w");
	folderdir(folderpath,fp);
	fclose(fp);
	fp = fopen(bufroute,"r");
	if(fp==NULL){
		errorlog("findinfolder","cannot open ",bufroute);
		return 0;
	}
	for( n = 0; c != EOF; ){
		strclr(dir);
		for( r = 0; c != EOF; r++ ){
		    c = fgetc(fp);
		    if(c=='\n'||c==EOF){
				dir[r] = 0;
				break;
			} else dir[r] = c;
		}
	    if(dir[0]==0) continue;
	    strcpy(FileDirTemp,folderpath);
		strcat(FileDirTemp,dir);
		n += find(handle,FileDirTemp);
	}
	fclose(fp);
	remove(bufroute);
	return n;
}
