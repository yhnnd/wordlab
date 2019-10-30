/*
* set data with (name,value)
* if data with that name existed, update it with new value
* otherwise, add new data with that name and value.
*/
int datacontainer::set(const std::string name,const std::string value) {
	if(number>=max) {
		printf("database has no space to allocate\n");
		return -1;
	} else if(name.empty()) {
		printf("illegal require to set a data without name\n");
		return -2;
	}
	int i = 0;
	for(i = 0; i < number; i++ ) {
		if( name == dataset[i].name ) break;
	}
	dataset[i].name = name;
	dataset[i].value = value;
	if(debug) {
		printf((i==number)?"setting ":"updating ");
		printf("data[%d] %s=%s\n",i,name.c_str(),value.c_str());
	}
	if(i==number) number++;// new data added
	return number;
}
