int exec(){
	int n=0,i=0,error=0;
	if(attr_n>0){
		for(n=0;n<attr_n;n++) attr[n].toString(n);
		getch();
	}
	for(n=0;cmds[n]!=-1;n++){
		switch(cmds[n]){
			case 101:if(i<=attr_n&&attr[i].req) i+=queryselect(); break;
			case 105:if(i<=attr_n&&attr[i].req) i+=queryupdate(); break;
			case 114:if(i<=attr_n&&attr[i].req) i+=queryprint(); break;
			case 115:if(i<=attr_n&&attr[i].req) i+=querysystem(); break;
			default: error++; execError(n); break;
		}
	}
	if(error) wait(-1,10,1,0);
	return error;
}
