bool AddIsSecure(ofstream &foutEN,ofstream &foutCH){
	int NOL[2];
	if(!foutEN){
		Dialog.output("database ENGLISH not opened!");
		return false;
	}else if(!foutCH){
		Dialog.output("database CHINESE not opened!");
		return false;
	}else if(db_is_secure(false,false)==false){
		Dialog.output("database damaged. unable to insert data!");
		return false;
	}
	return true;
}
