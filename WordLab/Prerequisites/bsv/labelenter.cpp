int prerequisites::bsvLabelEnter(PKC folder, PKC label, int x, const int y, int width, PKC color, void *spptr) {

	char route[128], labelname[32], labelvalue[32];
	int i = 0, r = 0;
    memset(labelname, 0, sizeof(labelname));
	for (i = 0, r = 0; label[i]!=0 && !strchr("=\"",label[i]); i++, r++) {
        labelname[r] = label[i];
    }
	strclr(labelname,r);

    memset(labelvalue, 0, sizeof(labelvalue));
	for (i = strindex(label,"\"") + 1, r = 0; label[i] != 0 && label[i] != '\"'; i++, r++) {
        labelvalue[r] = label[i];
    }
	strclr(labelvalue,r);

	strcpy(route,folder);
	if (strcmp(labelname,"button") == 0) { // open a Script file
		strcat(route,"main.js");
		// check script file
		const int max = filelines(route,1);
		if(max <= 0) {
			bsvError("<-ylw>( bsv label enter )<-red>( error )<-wte>( \\(",route,"\\) is void");
			return -1;
		}
		// check script processor
		if(spptr == NULL) {
			bsvError("<-ylw>( bsv label enter )","<-red>( error )","<-wte>( script unsupported");
			return -2;
		}
		// load script file
		std::string tempstr = "";
		std::vector<std::string> lines;
		std::ifstream fin(route);
		while (std::getline(fin,tempstr)) {
            lines.push_back(tempstr);
        }
		fin.close();
		// run script file
		((scriptprocessor*)spptr)->scriptLines(labelvalue, lines);
		return bsvLabelEnter(folder,"\"main\"",x,y,width,color,spptr);

	} else { // link to BSV file
		strcat(route, labelvalue);
		strcat(route,".bsv");
		// check bsv file
		const int max = filelines(route,1);
		if (max <= 0) {
			bsvError("<-ylw>( bsv label enter )<-red>( error )<-wte>( \\(",route,"\\) is void");
			return -1;
		}
		// load bsv file
		char msgs[max][256],*ptr[max];
		for (int i = 0; i<max; i++) {
            ptr[i] = msgs[i];
        }
		if (loadmsg((char*)msgs,route,max,256,1,1) <= 0) {
            return -1;
        }
		return bsvLines(ptr,max-1,width,folder,x,y,spptr);
	}
}