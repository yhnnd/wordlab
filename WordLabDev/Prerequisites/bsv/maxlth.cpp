int bsvmaxlth(PKC msg,PKC br1,PKC br2,PKC omit,PKC term){//copy this "<",">","()",";"
	int r,lth;
	for(r=0,lth=0;strchr(term,msg[r])==nullptr&&msg[r]!='\0';r++){
		if(strchr(br1,msg[r])) for(r++;!strchr(br2,msg[r]);r++);
		else if(strchr(omit,msg[r]));
		else lth++;
	}
	return lth;
}
