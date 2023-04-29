void Table::Adjust(tablerow item[],int *x,int *y,int *width,int *total){
	char key=0;
	for(;;key=getch()){
		if(key==13||key==8) break;
	    else if(isupper(key)) key-='A'-'a';
		     if(key=='a') (*x)--;
		else if(key=='d') (*x)++;
		else if(key=='w') (*y)--;
		else if(key=='s') (*y)++;
		else if(key=='e') (*width)--;
		else if(key=='f') (*width)++;
		else if(key=='q') (*total)--;
		else if(key=='z') (*total)++;
		clearScreen();
		ShowAll(item,0,*total,0,*x,*y,*width);
	}
}
