void Table::SearchNumber(tablerow item[],int x,int y,int width,int Total){
	char msgs[MAXLINES][LINEMAX]={
            " "," "," "," ",
            " 请输入數據"
            " "," "," "," "," "
	};
	int r, result = 0;
	char number[64];
	Frame(0,x,y,42,&msgs[0][0],0);
	gotoxy(20,y+5);
	std::cin >> number;
	gotoxy(20,y+6);
	for(r=1;r<=Total;r++) {
        if(item[r].SearchNumber(number)==1) {
            result++;
        }
    }
	gotoxy(20,y+7);
	std::cout << "共发现" << result << "个结果";
    fflush(stdin);
	getch();
}
