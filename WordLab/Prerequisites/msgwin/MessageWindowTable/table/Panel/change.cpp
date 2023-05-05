int Table::Change(tablerow *item,int row,int rowmax,int colmax,int x,int y,int width,int *begin) {
	y += y > 10 ? -6 : 3;
	char msg[6][LINEMAX]={
	" table change options",
	" modify row",
	" insert row above",
	" insert row below",
	" delete row",
	" quit"
	};
    const int menuWidth = 32;
	Frame(0, x, y, menuWidth, &msg[0][0],6);
	int option = Switch(x, y, menuWidth, &msg[0][0],6,LINEMAX,1);
	switch(option){
		case 1:
            item[row].Add(x,y,width);
        break;
		case 3:
            row++;//caution: no break
		case 2:
			rowmax++;
			item = (tablerow *)realloc(item,sizeof(tablerow)*(rowmax+1));
			for(int r=rowmax;r>row;r--) item[r].copy(item[r-1]);
			item[row].Add(x,y,width);
        break;
		case 4:
			rowmax--;
			(*begin)-=(*begin)?1:0;
			for(int r=row;r<=rowmax;r++) item[r].copy(item[r+1]);
			item = (tablerow *)realloc(item,sizeof(tablerow)*(rowmax+1));
		break;
		default:
        break;
	}
	return rowmax;
}
