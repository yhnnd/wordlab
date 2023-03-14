int Table::CheckSame(tablerow item[],int Total,int colmax){
	int r;
	char msgs[MAXLINES][LINEMAX]={
	    " ","""����ӵĔ����ڔ��������ѽ�����.",
		" ","""�o�����ԓ������Ո�޸�ԭ����.",
		" "};
	for(r=1;r<Total;r++)
	if(item[r].CheckSame(item[r],item[Total],colmax)==1){
	    Frame(0,6,6,40,&msgs[0][0],0);
	    wl_getch();
	    return 1;
	}
	return 0;
}
