// show all data
int datacontainer::printAllData() {
	int i = 0;
	char line[128];
	_table Table;
	Table.clear();
	// table head
	Table.setrowborder(78);
	snprintf(line,128,"%40s [%d/%d]","script data",number,max);
	Table.setrow(77,line).setrowborder();
	snprintf(line,128,"%32s","name");
	Table.setrow(3).setcol(5," No.").setcol(34,line).setcol(34," value").setrowborder();
	// table body
    if (number > 0) {
        for (i = 0; i < number; i++) {
            Table.setrow(3);
            snprintf(line, 128, "%3d", i);
            Table.setcol(5, line);
            snprintf(line, 128, "%32s", dataset[i].name.c_str());
            Table.setcol(34, line).setcol(34, dataset[i].value);
        }
    } else {
        Table.setrow(3);
        snprintf(line,128, "%3s", "");
        Table.setcol(5, line);
        snprintf(line, 128, "%32s", "");
        Table.setcol(34, line).setcol(34, "");
    }
	Table.setrowborder();
	Table.setcolborder('|');
	// print table
	printf("\n");
	Table.editor();
	Table.clear();
	return i;
}
