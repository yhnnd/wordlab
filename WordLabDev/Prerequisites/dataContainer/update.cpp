//update data with new name and new value
int datacontainer::update(const std::string & oldname,const std::string & name,const std::string & value) {
	if(number>=max) return -1;
	int i = 0;
	for(i = 0; i < number; i++ ) {
		if( oldname == dataset[i].name ) break;
	}
	if(i==number) return 0;//data not found
	dataset[i].name = name;
	dataset[i].value = value;
	if(debug) { // old data updated
		printf("update data[%d] <%s> to <%s=%s>\n",i,oldname,name,value);
	}
	return i;
}
