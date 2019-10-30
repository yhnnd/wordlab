int bsvLabelEnter(PKC folder, PKC label, int x, int y, int width, PKC color, void *spptr) {
	int bsvlines(char **,const int,int,const char *,int,int,void*);
	char route[128],labelname[32],labelvalue[32];
	int i=0,r=0;
	for(i=0,r=0; label[i]!=0&&!strchr("=\"",label[i]); i++,r++) labelname[r]=label[i];
	strclr(labelname,r);
	for(i=strindex(label,"\"")+1,r=0; label[i]!=0&&label[i]!='\"'; i++,r++) labelvalue[r]=label[i];
	strclr(labelvalue,r);
	strcpy(route,folder);
	if(strcmp(labelname,"button")==0) { // open a Script file
		strcat(route,"main.js");
		// check script file
		const int max=filelines(route,1);
		if(max<=0) {
			bsverror("<-ylw>( bsv label enter )<-red>( error )<-wte>( \\(",route,"\\) is void");
			return -1;
		}
		// check script processor
		if(spptr==NULL) {
			bsverror("<-ylw>( bsv label enter )","<-red>( error )","<-wte>( script unsupported");
			return -2;
		}
		// load script file
		std::string tempstr;
		std::vector<std::string> lines;
		std::ifstream fin(route);
		while(std::getline(fin,tempstr)) lines.push_back(tempstr);
		fin.close();
		// run script file
		((scriptprocessor*)spptr)->scriptlines(labelvalue,lines);
		return bsvLabelEnter(folder,"\"main\"",x,y,width,color,spptr);
		gotoxy(1,0);
	} else { // link to BSV file
		strcat(route,labelvalue);
		strcat(route,".bsv");
		// check bsv file
		const int max=filelines(route,1);
		if(max<=0) {
			bsverror("<-ylw>( bsv label enter )<-red>( error )<-wte>( \\(",route,"\\) is void");
			return -1;
		}
		// load bsv file
		char msgs[max][256],*ptr[max];
		for(int i=0; i<max; i++) ptr[i]=msgs[i];
		if(loadmsg((char*)msgs,route,max,256,1,1)<=0) return -1;
		// display bsv file name
		gotoxy(x,y-1);
		colorset(bsvcmdcolor(color));
		bsvline(route,width);
		gotoxymove(1,x,1,y);
		return bsvlines(ptr,max-1,width,folder,x,y,spptr);
	}
}
