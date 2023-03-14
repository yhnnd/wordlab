// show all data
int datacontainer::showall(){
	int i=0;
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
	for(i=0;i<number;i++){
		Table.setrow(3);
		snprintf(line,128,"%3d",i);
		Table.setcol(5,line);
		snprintf(line,128,"%32s",dataset[i].name.c_str());
		Table.setcol(34,line).setcol(34,dataset[i].value);
	}
	Table.setrowborder();
	Table.setcolborder('|');
	// print table
	std::cout<<std::endl;
	Table.editor();
	Table.clear();
	return i;
}
