// get the value of the data with that name
std::string datacontainer::getvalue(const std::string & name) {
	int i = 0;
	std::string value = "";
	for(i = 0; i < number; i++ ) {
		if( name == dataset[i].name ) {
			value = dataset[i].value;
			break;
		}
	}
	if (debug) {
		if (i < number) {
            printf("getting data[%d] %s=%s\n",i,name.c_str(),value.c_str());
        } else {
            printf("getting data (%s) failed\n",name.c_str());
        }
	}
	return value;
}

// return true if name is defined
bool datacontainer::has(const std::string & name) {
	int i = 0;
	for(i = 0; i < number; i++ ) {
		if( name == dataset[i].name ) {
			return true;
		}
	}
	return false;
}
