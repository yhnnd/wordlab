int WordSortCore(int lth,int number) {
	int NOL=0,sort=0;
	char c[200];
	FILE*fp=Library(lth,CH,"r");
	while(!feof(fp)) {
		if(fgets(c,200,fp)) NOL++;
		if(NOL==number) {
			sort=SortClassify(c);
			break;
		}
	}
	fclose(fp);
	return sort;
}
