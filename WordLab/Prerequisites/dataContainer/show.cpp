// show all data
int datacontainer::showall(){
	int i=0;
	char line[128];
	_table Table;
	Table.clear();
	// table head
	Table.setrowborder(78);
	sprintf(line,"%40s [%d/%d]","script data",number,max);
	Table.setrow(77,line).setrowborder();
	sprintf(line,"%32s","name");
	Table.setrow(3).setcol(5," No.").setcol(34,line).setcol(34," value").setrowborder();
	// table body
	for(i=0;i<number;i++){
		Table.setrow(3);
		sprintf(line,"%3d",i);
		Table.setcol(5,line);
		sprintf(line,"%32s",dataset[i].name.c_str());
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
