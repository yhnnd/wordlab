void load::PrintSoftwareVersion(int x,int y){
	_table VersionTable;
	VersionTable.setrowborder(57);
	//script processor
	VersionTable.setrow(5).setcol(8,"script")
	.setcol(10,"database").setcol(10,dataContainerVersion())
	.setcol(10,"exec").setcol(10,scriptVersion());
	//query shell
	VersionTable.setrow(5).setcol("query")
	.setcol("build").setcol(csvquery::constructorVersion())
	.setcol("exec").setcol(csvquery::executorVersion());
	//search engine
	VersionTable.setrow(5).setcol("search")
	.setcol("database").setcol(DatabaseVersion())
	.setcol("engine").setcol(SoftwareVersion());
	VersionTable.setrowborder().setcolborder('|');
	VersionTable.printtable(x,y);
	VersionTable.clear();
}
