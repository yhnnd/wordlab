void MessageWindow::SelectShowChange(int x,int y,int r1,int r2){
	int r;
	bool flag=1;
	if(r1>r2){r=r1;r1=r2;r2=r;flag=0;}
	for(r=r1+1;r<r2;r++){
		gotoxy(x,y+r);
		std::cout<<((flag)?"|/\\":"|\\/");
		}
	gotoxy(x,y+r1);
	std::cout<<((!flag)?"-->":"---");
	gotoxy(x,y+r2);
	std::cout<<((flag)?"-->":"---");
}
