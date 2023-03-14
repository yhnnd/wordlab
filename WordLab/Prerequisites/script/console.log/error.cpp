void scriptprocessor::consolelogerror(const std::string & format,const std::string & v1,const std::string & v2,const std::string & v3) {
	std::ofstream fout;
	fout.open(this->LogFolder+"debug.log",std::ios::app);
	if(fout.good()) {
		fout<<"<script>"<<CurrentScriptLine<<std::endl;
		char *line = (char *) malloc(sizeof(char)*128);
		snprintf(line,128,format.c_str(),v1.c_str(),v2.c_str(),v3.c_str());
		fout<<"<error>"<<line<<std::endl;
		free(line);
		fout.close();
	} else {
		errorlog("scriptprocessor.console.logerror","cannot open",this->LogFolder+"debug.log");
	}
}
