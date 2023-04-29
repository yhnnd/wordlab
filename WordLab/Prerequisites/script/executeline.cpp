void scriptprocessor :: executeline(const char *line) {
	// execute single-line script
	consolelogline(line);
	if(find(line,"function ")>=0) {
	} else if(find(line,"gotoxy")>=0) {
		scriptgotoxy(line);
	} else if(find(line,"getch()")>=0) {
		scriptgetch(line);//getch()
	} else if(find(line,"fgets")>=0) {
		scriptfgets(line);//fgets(route)
	} else if(find(line,"gets()")>=0) {
		scriptgetsvoid(line);//name=gets()
	} else if(find(line,"gets(")>=0) {
		scriptgets(line);//gets(name)
	} else if(find(line,"fputs(")>=0) {
		scriptfputs(line);
	} else if(find(line,"var")>=0) {
		var(line);
	} else if(find(line,"print")>=0) {
		prints(line);
	} else if(find(line,"remove(")>=0) {
		remove(line);
	} else if(find(line,"select")>=0) {
		select(line);
	} else if(find(line,"showalldata()")>=0) {
		dataset.showall();
	} else if(find(line,"strclr(")>=0) {
		scriptstrclr(line);
	} else {// execute expression
		std::string code_line(line);
		auto first_pos_of_space = code_line.find(" ");
		auto first_pos_of_equal = code_line.find("=");
		auto end_of_lval = std::min(first_pos_of_space,first_pos_of_equal);
		if(first_pos_of_space == std::string::npos) {
			end_of_lval = first_pos_of_equal;
		} else {
			end_of_lval = first_pos_of_space;
		}
		if(end_of_lval != std::string::npos) {
			auto lval = code_line.substr(0,end_of_lval);
			lval = get_left_value_name(lval);
			auto rval_str = trim(code_line.substr(first_pos_of_equal+1));
			float rval = get_right_value_value(rval_str);
			dataset.set(lval,tostring(rval));
		}
	}
}
