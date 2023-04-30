int querywhere() {
	std::string::size_type tokenpos=attr[attr_n].value.self.find("-");
	if(tokenpos!=std::string::npos) { //self conform with pattern "a-b"
		attr[attr_n].value.from.assign(attr[attr_n].value.self,0,tokenpos);
		attr[attr_n].value.to.assign(&(attr[attr_n].value.self.c_str()[tokenpos+1]));
	} else {
		attr[attr_n].value.from=attr[attr_n].value.self;
		attr[attr_n].value.to=attr[attr_n].value.self;
	}
	attr_n++;
    return 0;
}
