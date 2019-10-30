int scriptprocessor::scriptlines(const std::string FunctName,std::vector<std::string> const lines){
	std::cin.clear();
	std::cin.sync();
	brlv = 0;
	// scope levels
	Run.setInScopeFalse();
	Ignore.disable();
	ForLoop.disable();
	inInitClassFunct.setInScopeFalse();
	
	colorrecord(color);
	colorset(white);
	std::string line,functname;
	for(int i=0;i<lines.size();i++){
		line = lines[i];
		functname = FunctName;
		line.erase(0,line.find_first_not_of(" \t\v\r\n"));
		//scriptline(line.c_str(),functname.c_str());
		scriptline_div(line,functname);
	}
	colorreset(color);
}
