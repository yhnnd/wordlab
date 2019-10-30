int queryif(string msg){
	return attr[attr_n].req=maths::calc(msg_trim.c_str());
}
int queryelse(string msg){
	if(attr[attr_n-1].req==0){
		evalbr(msg_trim);
		return attr[attr_n-1].req=1;
	}
	else return 0;
}
