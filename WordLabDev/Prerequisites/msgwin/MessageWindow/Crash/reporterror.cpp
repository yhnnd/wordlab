bool MessageWindow::ErrorReport(const char route[]){
	bool flag=false;
	FILE * fp=NULL;
	if((fp=fopen(route,"r"))==NULL) flag=true;
	fclose(fp);
	std::cout<<"錯誤報告生成"<<((flag)?"失敗":"完畢");
	return flag;
    }
