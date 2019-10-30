void Table::ShowAll(tablerow item[],int begin,int max,int Class,int x,int y,int width){
	int r;
	Title(x,y,width,max);
	for(r=1;r<=max;r++){
	    gotoxy(x+4,y+2+r);
		colorset(backwhite);
		std::cout<<std::setw(4)<<r+begin;
		colorset(backgray);
		std::cout<<" ";
		if(item[r+begin].IsClass(Class)) item[r+begin].Out();
	}
	colorset(white);
}
