int scriptprocessor::scriptlines(const std::string FunctName, std::vector<std::string> const lines) {
	std::cin.clear();
	std::cin.sync();
	brlv = 0;
	// scope levels
	Run.setInScopeFalse();
	Ignore.disable();
	ForLoop.disable();
	inInitClassFunct.setInScopeFalse();
	
	colorrecord(color);
	colorset(lightwhite);
	std::string line,functname;
	for (int i = 0; i < lines.size(); i++) {
		line = lines[i];
		functname = FunctName;
		line.erase(0,line.find_first_not_of(" \t\v\r\n"));
		//scriptline(line.c_str(),functname.c_str());
		scriptline_div(line, functname);
	}
	colorreset(color);
    return 0;
}


int scriptprocessor::printAllScriptLines() {
    _table Table;
    Table.clear();
    // table head
    Table.setrowborder(78);

    char line[128];
    snprintf(line,128,"%40s [%zu]","script lines", this->scriptTextLines.size());
    Table.setrow(77,line).setrowborder();
    snprintf(line, 128, "%34s","script line");
    Table.setrow(2).setcol(5," No.").setcol(70, line).setrowborder();
    // table body
    for(int i = 0; i < this->scriptTextLines.size(); i++) {
        Table.setrow(2);
        snprintf(line,128, "%3d", i);
        Table.setcol(5, line);
        snprintf(line, 128, "%-70s", this->scriptTextLines[i].c_str());
        Table.setcol(70, line);
    }
    Table.setrowborder();
    Table.setcolborder('|');
    // print table
    printf("\n");
    Table.editor();
    Table.clear();
    return this->scriptTextLines.size();
}