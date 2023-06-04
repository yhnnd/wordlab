int Table::Add(tablerow *item,int Total,int colmax,int x,int y,int width) {
	item = (tablerow *) realloc(item, sizeof(tablerow) * (Total + 1));
	item[++Total].Add(x,y,width);

	if (Total >= 2) {
        if(CheckSame(item,Total,colmax) == 1) {
            --Total;
        }
    }
	return Total;
}
