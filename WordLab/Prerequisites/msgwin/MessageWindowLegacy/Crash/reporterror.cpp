bool MessageWindow::ErrorReport(const char route[]){
	bool flag=false;
	FILE * fp=NULL;
	if((fp=fopen(route,"r"))==NULL) flag=true;
	fclose(fp);
	std::cout<<"Error Report Generating "<<((flag)?"failed":"success");
	return flag;
}
