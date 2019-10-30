int scriptprocessor::prints(const char *line){
	name = getparam(line);
	if(name[0]=='\"'){// parameter is string
		value = removebrackets(name,"\"","\"");
	} else {// parameter is name
		name = get_left_value_name(name);
		value = dataset.getvalue(name);
	}
	print(value);
	return 0;
}
