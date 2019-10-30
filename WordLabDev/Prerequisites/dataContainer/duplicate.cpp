int datacontainer::duplicate(const std::string & destname,const std::string & srcname) {
	if(destname.empty()) {
		printf("illegal require to set an object without a name\n");
		return -2;
	} else if( destname == srcname ) {
		printf("illegal require to set object <%s> that exists\n",destname.c_str());
		return -3;
	}
	int i = 0;
	for( i = 0; i < number; i++ ) {
		if(srcname==dataset[i].name) break;
	}
	if(i==number) {
		printf("error: cannot copy object <%s> that doesn't exist\n",srcname.c_str());
		return -4;
	}
	if(number>=max) {
		printf("database has no space to allocate\n");
		return -1;
	}
	//adding new object
	dataset[number].name = destname;
	dataset[number].value = dataset[i].value;
	number++;
	//copying members of source object
	std::string membername;
	for( i = 0; i < number; i++ ) {
		if ( dataset[i].name.find(srcname+".")==0 ) {
			//a member of source object has been found
			membername = destname;
			membername += ".";
			membername += dataset[i].name.substr(dataset[i].name.find(".")+1);
			if(number >= max) {
				printf("database has no space to allocate\n");
				return -1;
			}
			if ( debug ) printf("duplicate() setting data[%d] %s=%s\n",i,membername.c_str(),dataset[i].value.c_str());
			//adding member of dest object
			dataset[number].name = membername;
			dataset[number].value = dataset[i].value;
			number++;
		}
	}
	return number;
}
