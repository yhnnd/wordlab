int querynext(string msg){
	string::size_type i=msg.find(" "),j=msg.find(" ",++i);
	msg_trim.assign(msg,i,j-i);
	i=msg_trim.find("=");
	if(i!=string::npos){
		attr[attr_n].name.assign(msg_trim,0,i);
		attr[attr_n].value.self.assign(msg_trim,i+1,1024);
		return 1;
	}
	return 0;
}
