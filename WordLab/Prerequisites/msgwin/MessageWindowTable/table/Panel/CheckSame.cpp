int Table::CheckSame(tablerow item[],int Total,int colmax){
	int r;
	char msgs[MAXLINES][LINEMAX]={
	    " ","""新添加的數據在數據庫中已經存在.",
		" ","""無法添加該新數據，請修改原數據.",
		" "};
	for(r=1;r<Total;r++)
	if(item[r].CheckSame(item[r],item[Total],colmax)==1){
	    Frame(0,6,6,40,&msgs[0][0],0);
	    wl_getch();
	    return 1;
	}
	return 0;
}
