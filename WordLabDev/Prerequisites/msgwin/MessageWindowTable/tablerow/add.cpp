int tablerow::setcol(int x,int y,char *col){
	gotoxy(x,y);
	if(col[0]){
		std::cout<<col;
		gotoxy(x,y);
	}
	std::cin>>col;
}

int tablerow::Add(int x,int y,int width){
	char msg[3][LINEMAX]={
#include "M/AddNewItem.txt"
	};
	MessageWindow.Frame(0,x,y,width,&msg[0][0],3);
	setcol(x+4,y+2,col[1]);
	setcol(x+4+1+strlen(col[1]),y+2,col[2]);
	setcol(x+4+2+strlen(col[1])+strlen(col[2]),y+2,col[3]);
	itoa(MessageWindow.ConfirmSwitch(12,x+4,y+2,width+5,1),col[0],10);
}
