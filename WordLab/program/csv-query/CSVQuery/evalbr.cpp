int evalbr(string cmd_in){
	if(cmd_in.find("if(")==0){
		attr[attr_n].req=maths::calc(cmd_in.substr(3,1024).c_str());
	}else if(cmd_in.find("print(")==0){
		print_msg=cmd_in.substr(cmd_in.find("(")+1,cmd_in.find(")"));
		cmds[n++]=114;
	}else if(cmd_in=="*"){//select all
			attr[attr_n].name="lth";
			attr[attr_n].value.from="1";
			attr[attr_n].value.to="30";
			attr_n++;
	}else{
		const char *labels[]={"\\<eval\\>","error","not found",cmd_in.c_str()};
		queryerror(labels);
	}
	return 0;
}
