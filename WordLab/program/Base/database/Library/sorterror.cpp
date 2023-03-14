int sortLibError(int n,const string msg=""){
	switch(abs(n)){
		case 0:popup("sortlib: library ",msg.c_str()," has been sorted",0);break;
		case 1:popup("sortlib:<ylw-red>( error )<red->(database not found",-1);break;
		case 2:popup("sortlib:<ylw-red>( error )<red->(memory not enough",-1);break;
		case 3:popup("sortlib:<ylw-red>( error )<red->(failed to read database",-1);break;
		case 4:popup("sortlib:<ylw-red>( error )<red->(override invalid data <ylw->(",msg.c_str(),")",-1);break;
		case 5:popup("sortlib:<ylw-red>( error )<red->(failed to record data",-1);break;
		case 6:popup("sortlib:<ylw-red>( error )<red->(failed to rewrite database",-1);break;
		case 7:popup("sortlib:<ylw-red>( error )<red->( no permission to access the database",-1);break;
		case 8:popup("sortlib:<ylw-red>( error )<red->( no database selected",-1);break;
		default:popup("sortlib:<ylw-red>( error )<red->(unknown error",-1);break;
	}
	return n;
}
