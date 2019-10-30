//init class member
void scriptprocessor::varInitClassMember(const std::string & name,const std::string & value,const std::string & begintoken,const std::string & endtoken) {
	std::string subname = "", subvalue = "";
	bool flag = false;
	int i = 0;
	for( i = value.find(begintoken) + 1; i < value.length(); i++ ) {
		if(value[i]==':') {
			subvalue = "";
			flag = true;
		} else if(value[i]==','||endtoken.find(value[i])!=std::string::npos) {
			std::string subnamefull;
			subnamefull = name;
			subnamefull += ".";
			subnamefull += subname;
			dataset.set(subnamefull,subvalue);
			consolelog("variable (class %s)<%s=%s> has been added",name,subnamefull,subvalue);
			subname = "";
			flag = false;
		} else if(flag==false) subname += value[i];
		else if(flag==true) subvalue += value[i];
	}
}
