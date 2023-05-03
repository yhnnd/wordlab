int scriptprocessor::var(const char *line) {
	static std::string classname;
	name = getname(line);
	value = getvalue(line);
	if(	name.empty() ) {
		consolelogerror("variable without a name");
		return 0;
	} else if(varIsArray(name,line)) { //variable is an array
		varInitArray(name,value);
		return 0;
	} else if(varIsClassJson(name,value,line)) { //variable is a class defined with json
		consolelog("var3 init class <%s> with member <%s>",name,value);
		dataset.set(name,value);
		varInitJsonClassMember(name,value,"{","}");
		return 0;
	} else if(varIsClassFunct(name,value,line)) { //variable is a object constructing function
		inInitClassFunct.activate(brlv);
		consolelog("var4 init class <%s> by function <%s>",name,value);
		classname = name;
		dataset.set(name,value);
		varInitClassMember(name,value,"(",")");
		return 0;
	} else if(inInitClassFunct.inScope(brlv)) {
		//if(object.member.name==value) object.member.value=value
		std::string subname = "", subvalue = "";
		subname = classname;
		subname += ".";
		subname += value;
		if(dataset.has(subname)) {
			subvalue = classname;
			subvalue += ".";
			subvalue += name;
			dataset.update(subname,subvalue,subname);
		}
		return 0;
	} else inInitClassFunct.disable();
	if(value.empty()) {
		consolelogerror("variable <%s> has no value",name);
		return 0;
	} else if(value[0]=='\"') { // value is string
		removebrackets(value,"\"","\"");
		dataset.set(name,value);
		return 0;
	} else if(value[0]=='-'||isdigit(value[0])) {
		for(;;) {
			int i=0;
			for(i=0; value[i]!=0; i++) if(!(isdigit(value[i])||value[i]=='-')) break;
			if(value[i]==0) break;// value is a digit
			else value = toString(maths::calc(value));// value is an expression
		}
		dataset.set(name,value);
		return 0;
	} else if(value[0]) {
		int i = value.find("("), j = value.find("'"), k = value.find("\"");
		if(i>=0&&(i<j||j<0)&&(i<k||k<0)) { //value is a class construct function
			consolelog("var9 init object <%s> by function <%s>",name,value);
			std::string classname, classMemberValues;
			classname = value.substr(0,i);
			classMemberValues = value.substr(i);
			varCallClassFunct(classname,name,classMemberValues);
		} else { // value is an object
			dataset.duplicate(name,value);
		}
		return 0;
	}
	return -1;
}
