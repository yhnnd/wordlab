int Table::Panel(tablerow item[],int Total,int colmax,const char *filename,int *x,int *y,int *width,int *total){
	int key=0;
	for(;;){
	    key=PanelMenu(*x,*y+2,16);
	         if(key== 1) Total=Add(item,Total,colmax,*x,*y,*width);
	    else if(key== 2) Save(item,filename,Total);
	    else if(key== 3) SearchName(item,*x,*y+4,*width,Total);
	    else if(key== 4) SearchNumber(item,*x,*y+4,*width,Total);
	    else if(key== 5) Adjust(item,x,y,width,total);
	    else if(key== 6) Report(*x,*y+2,*width,8,ReportFileRoute);
	    else break;
	}
	return Total;
}
