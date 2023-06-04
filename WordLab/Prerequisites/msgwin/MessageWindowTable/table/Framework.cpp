void Table::table(const char *filename, int x, int y, int width) {
	const int rowMax = filelines(filename, true);
	if (rowMax <= 0) {
		errorlog("table","invalid file ",filename);
		return;
	}
	tablerow *item = (tablerow *) calloc (rowMax, sizeof(tablerow));
	if(item == nullptr){
		errorlog("table","insufficient memory to allocate");
		return;
	}
	int Total = MessageWindowLoad(item, filename);
	int a = 1, Class = 0, colMax = 8;
	int begin = 0, max = (Total>18)?18:Total;

	MessageWindow::init();

	for (;;) {
	    ShowAll(item, begin, max, Class, x, y, width);
	    a = Scroll(x,y+2,width,max+2,a);
        if (a == 0) {
            break;
        } else if(a==-2&&begin>0) {
            begin--;
        } else if(a==-3&&begin+max<Total) {
            begin++;
        } else if(a>0&&a<=max) {
            Total = Change(item,a+begin,Total,colMax,x,y+a,width,&begin);
        } else if(a == max + 1) {
            Class=ListSwitch(16,x,y,width)-1;
        } else if(a == max + 2) {
            Total = Panel(item,Total,colMax,filename,&x,&y,&width,&max);
        }
	    limit(max,Total,0,18);
    }
	free(item);
}
